#version 330

in vec2 fTex;

layout (location = 0) out vec4 pCol;

uniform float zNear;
uniform float zFar;
uniform sampler2D color;
uniform sampler2D depth;

uniform float fogRate;
uniform vec4 fogColor;

vec4 lerp(vec4 a, vec4 b, float x) {
	return (1.0 - x) * a + x * b;
}

void main() {
	float dcomp = texture2D(depth, fTex).x;
    //float zpos = 2.0 * zNear * zFar / (zFar + zNear - (2.0 * dcomp - 1.0) * (zFar - zNear));
	//float k = zpos / zFar;

	//pCol = lerp(texture2D(color, fTex), fogColor, max(k - 1.0 + fogRate, 0.0) / fogRate);
	//pCol = texture2D(color, fTex);
	//pCol = vec4(dcomp, dcomp, dcomp, 1.0);
}