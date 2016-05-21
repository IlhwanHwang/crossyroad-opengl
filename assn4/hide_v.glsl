#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

out vec4 fPosEye;
out vec3 fNorm;

uniform mat4 modelview;
uniform mat4 eyeview;
uniform mat4 projection;

void main() {
	fPosEye = eyeview * modelview * vPos / vPos.w;
	fNorm = normalize((eyeview * modelview * vec4(vNorm, 0.0)).xyz);
    gl_Position = projection * fPosEye;
}