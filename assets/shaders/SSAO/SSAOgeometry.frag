#version 410 core

layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;

in vec3 normal;
in vec3 fragPos;

void main(){
    gPosition = fragPos;
    gNormal = normalize(normal);
}