#version 330

in vec2 fTex;
in vec4 fPosEye;
in vec3 fIntensity;
in vec3 fSpecular;
in vec3 fNorm;

uniform sampler2D color;
uniform sampler2D normal;
uniform vec2 uvOffset;

layout (location = 0) out vec4 pDiffuse;
layout (location = 1) out vec4 pPosition;
layout (location = 2) out vec4 pNormal;

void main() {
	vec4 samplePoint = texture2D(color, fTex + uvOffset);
	if (samplePoint.a < 0.5)
		discard;

	pDiffuse = vec4(samplePoint.xyz * fIntensity + fSpecular, samplePoint.a);
	pPosition = fPosEye;
	pNormal = vec4(fNorm, 0.0);
}