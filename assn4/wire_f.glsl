#version 330

layout (location = 0) out vec4 pDiffuse;
layout (location = 1) out vec4 pNormal;
layout (location = 2) out vec4 pPosition;

vec4 fCol = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
	pDiffuse = fCol;
	pNormal = fCol;
	pPosition = fCol;
}