#version 330
#define LIGHT_MAX 32

layout (location = 0) in vec4 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vNorm;

uniform mat4 modelview;
uniform mat4 eyeview;
uniform mat4 projection;

uniform vec4 lightAmbient;
uniform int lightCount;
uniform vec4 lightColor[LIGHT_MAX];
uniform vec4 lightPosition[LIGHT_MAX];
uniform vec4 lightEye;

uniform float specularPower;
uniform float specularLightness;

out vec2 fTex;
out vec4 fPosEye;
out vec3 fIntensity;
out vec3 fSpecular;
out vec3 fNorm;

void main() {
	fNorm = normalize(modelview * vec4(vNorm, 0.0)).xyz;
	vec4 fPos = modelview * vPos / vPos.w;
	fPosEye = eyeview * fPos;
    gl_Position = projection * fPosEye;

	fTex = vTex;

	fIntensity = lightAmbient.rgb * lightAmbient.a;
	fSpecular = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < lightCount; i++) {
		vec3 N, L, R, V, uL;
		float I, S;
		N = fNorm;

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

		fIntensity += lightColor[i].rgb * lightColor[i].a * I;
		fSpecular += lightColor[i].rgb * lightColor[i].a * S;
	}

	fNorm = normalize((eyeview * vec4(fNorm, 0.0)).xyz);
}