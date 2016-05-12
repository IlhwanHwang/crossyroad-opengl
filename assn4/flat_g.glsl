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

in vec4 gPos[];
in vec2 gTex[];

out vec4 fPos;
out vec2 fTex;
out vec3 fNorm;

out vec3 fIntensity;

void main() {
	vec3 intensity, specular;
	intensity = lightAmbient.rgb * lightAmbient.a;

	vec3 N;
	N = cross(gPos[1].xyz - gPos[0].xyz, gPos[2].xyz - gPos[1].xyz);
	N = normalize(N);

	for (int i = 0; i < lightCount; i++) {
		vec3 L, uL;
		float I;

		if (lightPosition[i].w != 0.0) {
			uL = lightPosition[i].xyz - fPos.xyz;
		}
		else {
			uL = lightPosition[i].xyz;
		}
		L = normalize(uL);
		I = max(dot(L, N), 0.0);

		if (lightPosition[i].w != 0.0) {
			I /= length(uL);
		}

		intensity += lightColor[i].rgb * lightColor[i].a * I;
	}

	for (int i = 0; i < 3; i++) {
		gl_Position = gl_in[i].gl_Position;
		fPos = gPos[i];
		fTex = gTex[i];
		fNorm = N;
		fIntensity = intensity;
		EmitVertex();
	}
    EndPrimitive();
}