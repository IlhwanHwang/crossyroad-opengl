#version 330
#define LIGHT_MAX 32

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform vec4 lightAmbient;
uniform int lightCount;
uniform vec4 lightColor[LIGHT_MAX];
uniform vec4 lightPosition[LIGHT_MAX];
uniform vec4 lightEye;

uniform float specularPower;
uniform float specularLightness;

uniform mat4 eyeview;

in vec4 gPos[];
in vec4 gPosEye[];
in vec2 gTex[];

out vec2 fTex;
out vec4 fPosEye;
out vec3 fIntensity;
out vec3 fSpecular;
out vec3 fNorm;

void main() {
	vec3 intensity, specular;
	intensity = lightAmbient.rgb * lightAmbient.a;
	specular = vec3(0.0, 0.0, 0.0);

	vec3 N;
	N = cross(gPos[1].xyz - gPos[0].xyz, gPos[2].xyz - gPos[1].xyz);
	N = normalize(N);

	vec4 fPos = (gPos[0] + gPos[1] + gPos[2]) / 3.0;

	for (int i = 0; i < lightCount; i++) {
		vec3 L, uL, R, V;
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

	for (int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		fTex = gTex[i];
		fPosEye = gPosEye[i];
		fIntensity = intensity;
		fSpecular = specular;
		fNorm = normalize((eyeview * vec4(N, 0.0)).xyz);
		EmitVertex();
	}
    EndPrimitive();
}