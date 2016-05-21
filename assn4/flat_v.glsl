#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 modelview;
uniform mat4 eyeview;
uniform mat4 projection;

out vec4 gPos;
out vec4 gPosEye;
out vec2 gTex;

void main() {
	gPos = modelview * vPos / vPos.w;
	gPosEye = eyeview * gPos;
    gl_Position = projection * gPosEye;

	gTex = vTex;
}