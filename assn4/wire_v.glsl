#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 modelview;
uniform mat4 projection;

void main() {
    gl_Position = projection * modelview * vPos / vPos.w;
}