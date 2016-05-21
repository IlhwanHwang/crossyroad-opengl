#version 330

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 modelview;
uniform mat4 eyeview;
uniform mat4 projection;

out vec2 gTex;
out vec4 gPos;
out vec4 gPosEye;
out vec3 gNorm;

void main() {
	gTex = vTex;
	gNorm = normalize((modelview * vec4(vNorm, 0.0)).xyz);
	gPos = modelview * vPos / vPos.w;
	gPosEye = eyeview * gPos;
    gl_Position = projection * gPosEye;
}