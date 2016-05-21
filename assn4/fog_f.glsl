#version 330

in vec2 fTex;

layout (location = 0) out vec4 pCol;

uniform float zFar;
uniform sampler2D depth;

uniform float fogRate;
uniform vec4 fogColor;

vec4 lerp(vec4 a, vec4 b, float x) {
	return (1.0 - x) * a + x * b;
}

void main() {
	float dcomp = texture2D(depth, fTex).z;
	if (dcomp == 0.0) {
		pCol = fogColor;
	}
	else {
		float k = -dcomp / zFar;
		pCol = vec4(fogColor.rgb, max(k - 1.0 + fogRate, 0.0) / fogRate);
	}
}