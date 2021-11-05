#version 410 core

// PN TRIANGLES TESSELLATION SHADER

// number of control pts
layout (vertices = 1) out;


uniform int tes_lod;

// from vertex shader
in vec3 WorldPos_vert_out[];
in vec2 TexCoords_vert_out[];
in vec3 Normal_vert_out[];

struct CtlTriangle{
    vec3 p_003, p_012,p_021,p_030,
            p_102,p_111,p_120,
               p_201,p_210,
                  p_300;
    vec3 Normal[3];
    vec2 TexCoord[3];
};
//send control triangle to eval shader
patch out CtlTriangle CtlTri;

vec3 orthoProj(vec3 orig, vec3 target, vec3 normal);

void main(){
    // pass original points
    for (int i = 0 ; i < 3 ; i++) {
       CtlTri.Normal[i] = Normal_vert_out[i];
       CtlTri.TexCoord[i] = TexCoords_vert_out[i];
    }
    // set tessellation levels
    gl_TessLevelOuter[0] = tes_lod;
    gl_TessLevelOuter[1] = tes_lod;
    gl_TessLevelOuter[2] = tes_lod;
    gl_TessLevelInner[0] = tes_lod;

    //1. original points of triangle
    CtlTri.p_030 = WorldPos_vert_out[0];
    CtlTri.p_003 = WorldPos_vert_out[1];
    CtlTri.p_300 = WorldPos_vert_out[2];

    vec3 edge1 = CtlTri.p_300 - CtlTri.p_003;
    vec3 edge2 = CtlTri.p_030 - CtlTri.p_300;
    vec3 edge3 = CtlTri.p_003 - CtlTri.p_030;


    //2. points on edges
    CtlTri.p_012 = CtlTri.p_030 + edge3 * 2.0 / 3.0; //at 2/3
    CtlTri.p_021 = CtlTri.p_030 + edge3 / 3.0;       //at 1/3
    CtlTri.p_201 = CtlTri.p_003 + edge1 * 2.0 / 3.0;
    CtlTri.p_102 = CtlTri.p_003 + edge1 / 3.0;
    CtlTri.p_120 = CtlTri.p_300 + edge2 * 2.0 / 3.0;
    CtlTri.p_210 = CtlTri.p_300 + edge2 / 3.0;
    // project edge points
    CtlTri.p_021 = orthoProj(CtlTri.p_021, CtlTri.p_030,CtlTri.Normal[0]);
    CtlTri.p_012 = orthoProj(CtlTri.p_012, CtlTri.p_003,CtlTri.Normal[1]);
    CtlTri.p_102 = orthoProj(CtlTri.p_102, CtlTri.p_003,CtlTri.Normal[1]);
    CtlTri.p_201 = orthoProj(CtlTri.p_201, CtlTri.p_300,CtlTri.Normal[2]);
    CtlTri.p_210 = orthoProj(CtlTri.p_210, CtlTri.p_300,CtlTri.Normal[2]);
    CtlTri.p_120 = orthoProj(CtlTri.p_120, CtlTri.p_030,CtlTri.Normal[0]);


    //3. center of triangle
    vec3 triCenter = (CtlTri.p_003 + CtlTri.p_030 + CtlTri.p_300) / 3.0;

    vec3 edgesCenter = (CtlTri.p_021 + CtlTri.p_012 + CtlTri.p_102 +
                          CtlTri.p_201 + CtlTri.p_210 + CtlTri.p_120) / 6.0;
    
    CtlTri.p_111 = edgesCenter+(edgesCenter - triCenter) / 2.0;
}

vec3 orthoProj(vec3 orig, vec3 target, vec3 normal){
    vec3 v = orig - target;
    float Len = dot(v, normal);
    vec3 d = Len * normal;
    return (orig - d);
}