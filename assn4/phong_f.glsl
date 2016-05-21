#version 330
#define LIGHT_MAX 32

in vec2 fTex;
in vec4 fPos;
in vec4 fPosEye;
in vec3 fNorm;
in mat3 fTBN;

uniform vec4 lightAmbient;
uniform int lightCount;
uniform vec4 lightColor[LIGHT_MAX];
uniform vec4 lightPosition[LIGHT_MAX];
uniform vec4 lightEye;

uniform float specularPower;
uniform float specularLightness;

uniform mat4 eyeview;

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

	vec3 intensity, specular;
	intensity = lightAmbient.rgb * lightAmbient.a;
	specular = vec3(0.0, 0.0, 0.0);

	vec3 sN, N;
	sN = texture2D(normal, fTex + uvOffset).xyz * 2.0 - 1.0;
	N = normalize(fTBN * sN);

	for (int i = 0; i < lightCount; i++) {
		vec3 L, R, V, uL;
		float I, S;

		if (lightPosition[i].w != 0.0) {
			uL = lightPosition[i].xyz - fPos.xyz;
		}
		else {
			uL = lightPosition[i].xyz;
		}
		L = normalize(uL);
		R = reflect(L, N);
		V = normalize(lightEye.xyz - fPos.xyz);

		I = max(dot(L, N), 0.0);
		S = pow(max(-dot(V, R), 0.0), specularPower) * specularLightness;

		if (lightPosition[i].w != 0.0) {
			I /= length(uL);
			S /= length(uL);
		}

		intensity += lightColor[i].rgb * lightColor[i].a * I;
		specular += lightColor[i].rgb * lightColor[i].a * S;
	}

	pDiffuse = vec4(samplePoint.xyz * intensity + specular, samplePoint.a);
	pPosition = fPosEye;
	pNormal = vec4(normalize((eyeview * vec4(N, 0.0)).xyz), 0.0);
}