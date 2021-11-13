#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;


out vec3 Normal_frag;
out vec3 FragPos_frag;
out vec2 TexCoords_frag;
out vec4 FragPos_lightSpace_frag[5];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


uniform mat4 lightSpaceMatrix[5];


void main(){

    FragPos_frag = vec3((model*vec4(aPos,1.0)));
    Normal_frag = mat3(transpose(inverse(model))) * aNormal;
    Normal_frag = normalize(Normal_frag);
    TexCoords_frag = aTexCoords;

    for (int i = 0; i<5;i++){
        FragPos_lightSpace_frag[i] = lightSpaceMatrix[i] * vec4(FragPos_frag, 1.0);
    }
    gl_Position = projection * view * vec4(FragPos_frag, 1.0);
}

