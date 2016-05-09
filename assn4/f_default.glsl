#version 150

in vec2 pTex;
in vec4 pCol;
in float pDepth;
out vec4 fColor;

uniform sampler2D tex;
uniform vec4 fog;
uniform float fograte;
uniform float zfar;

vec4 lerp(vec4 a, vec4 b, float x) {
	return x * b + (1.0 - x) * a;
}

void main()
{
	float d = pDepth / zfar;
    fColor = pCol * texture2D(tex, pTex);
	fColor = lerp(fColor, fog, min(1.0, max(0.0, (d - fograte) / (1.0 - fograte))));
}
