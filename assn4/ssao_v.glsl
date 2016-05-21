#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;

out vec2 fTex;

void main() {
    gl_Position = vPos;
	fTex = vTex;
}