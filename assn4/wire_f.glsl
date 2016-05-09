#version 330

layout (location = 0) out vec4 pDiffuse;
layout (location = 1) out vec4 pNormal;
layout (location = 2) out vec4 pPosition;

void main()
{
	pDiffuse = vec4(0.0, 0.0, 0.0, 1.0);
	pNormal = vec4(0.0, 0.0, 0.0, 1.0);
	pPosition = vec4(0.0, 0.0, 0.0, 1.0);
}