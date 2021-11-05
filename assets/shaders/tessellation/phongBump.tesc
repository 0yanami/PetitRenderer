#version 410 core

// BUMP MAP TESSELLATION SHADER

// number of control pts
layout (vertices = 3) out;

uniform vec3 viewPos;

uniform int tes_lod0;
uniform int tes_lod1;
uniform int tes_lod2;

// from vertex shader
in vec3 WorldPos_vert_out[];
in vec2 TexCoords_vert_out[];
in vec3 Normal_vert_out[];

// to tes eval shader
out vec3 WorldPos_ctl_out[];
out vec2 TexCoords_ctl_out[];
out vec3 Normal_ctl_out[];

float getLod(float d1, float d2);

void main(){
    // pass ctl pts
    WorldPos_ctl_out[gl_InvocationID] = WorldPos_vert_out[gl_InvocationID];
    TexCoords_ctl_out[gl_InvocationID] =  TexCoords_vert_out[gl_InvocationID];
    Normal_ctl_out[gl_InvocationID] = Normal_vert_out[gl_InvocationID];
    // get dist camera-vertex
    float diste0 = distance(viewPos,WorldPos_ctl_out[0]);
    float diste1 = distance(viewPos,WorldPos_ctl_out[1]);
    float diste2 = distance(viewPos,WorldPos_ctl_out[2]);
    // set lod for each edge
    gl_TessLevelOuter[0] = getLod(diste1,diste2);
    gl_TessLevelOuter[1] = getLod(diste2,diste0);
    gl_TessLevelOuter[2] = getLod(diste0,diste1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}

// compute tess level with edge to camera distance
float getLod(float d1, float d2)
{
    // get average dist of edge from camera
    float avg = (d1 + d2) / 2.0;

    // low distance, high lod
    if (avg <= 2.0) {
        return tes_lod0;
    }
    else if (avg <= 5.0) {
        return tes_lod1;
    }
    else {
        return tes_lod2;
    }
}