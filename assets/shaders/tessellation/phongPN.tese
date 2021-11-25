#version 410 core

// PN TRIANGLES TESSELLATION SHADER

layout(triangles, equal_spacing, ccw) in;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix[5];

struct CtlTriangle{
    vec3 p_003, p_012,p_021,p_030,
            p_102,p_111,p_120,
               p_201,p_210,
                  p_300;
    vec3 Normal[3];
    vec2 TexCoord[3];
};
// triangle from control shader
patch in CtlTriangle CtlTri;

out vec3 FragPos_eval_out;
out vec2 TexCoord_eval_out; 
out vec3 Normal_eval_out;
out vec4 Fragpos_lightSpace_eval_out[5];

// get interpolation between 3 vectors
vec2 interp2D(vec2 v0, vec2 v1, vec2 v2);
vec3 interp3D(vec3 v0, vec3 v1, vec3 v2);

void main(){
    // interpolate and send to frag shader
    TexCoord_eval_out = interp2D(CtlTri.TexCoord[0], CtlTri.TexCoord[1], CtlTri.TexCoord[2]);
    Normal_eval_out = interp3D(CtlTri.Normal[0], CtlTri.Normal[1], CtlTri.Normal[2]);
    Normal_eval_out = normalize(Normal_eval_out);
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    float w = gl_TessCoord.z;

    vec3 bezier = CtlTri.p_300 * pow(w, 3) +
                  CtlTri.p_030 * pow(u, 3) +
                  CtlTri.p_003 * pow(v, 3) +
                  CtlTri.p_210 * 3.0 * pow(w, 2) * u +
                  CtlTri.p_120 * 3.0 * w * pow(u, 2) +
                  CtlTri.p_201 * 3.0 * pow(w, 2) * v +
                  CtlTri.p_021 * 3.0 * pow(u, 2) * v +
                  CtlTri.p_102 * 3.0 * w * pow(v, 2) +
                  CtlTri.p_012 * 3.0 * u * pow(v, 2) +
                  CtlTri.p_111 * 6.0 * w * u * v;
    FragPos_eval_out = bezier;
    for (int i = 0; i<5;i++){
        Fragpos_lightSpace_eval_out[i] = lightSpaceMatrix[i] * vec4(FragPos_eval_out, 1.0);
    }
    gl_Position = projection * view * vec4(bezier,1.0);
}

vec2 interp2D(vec2 v0, vec2 v1, vec2 v2){
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interp3D(vec3 v0, vec3 v1, vec3 v2){
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}