#version 330

layout (location = 0) out vec4 pDiffuse;
layout (location = 1) out vec4 pPosition;
layout (location = 2) out vec4 pNormal;

uniform sampler2D color;
uniform sampler2D normal;

in vec4 fPosEye;
in vec3 fNorm;
vec4 fCol = vec4(0.8, 0.9, 1.0, 1.0);

void main() {
	pDiffuse = fCol;
	pPosition = fPosEye;
	pNormal = vec4(fNorm, 0.0);
}