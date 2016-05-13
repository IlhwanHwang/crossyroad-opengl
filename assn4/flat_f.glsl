#version 330

in vec4 fPos;
in vec2 fTex;
in vec3 fNorm;

in vec3 fIntensity;

uniform sampler2D tex;
uniform vec2 uvOffset;

layout (location = 0) out vec4 pDiffuse;
layout (location = 1) out vec4 pNormal;
layout (location = 2) out vec4 pPosition;

void main() {
	vec4 samplePoint = texture2D(tex, fTex + uvOffset);
	if (samplePoint.a < 0.5)
		discard;

	pDiffuse = vec4(samplePoint.xyz * fIntensity, samplePoint.a);
	pNormal = vec4(fNorm, 1.0);
	pPosition = fPos;
}