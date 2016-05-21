#version 330

#define RADIUS 2
#define FRADIUS 2.0

in vec2 fTex;

uniform sampler2D tex;
uniform float texelw;
uniform float texelh;

layout (location = 0) out vec4 pCol;

void main() {
	float w = 0.0;
	pCol = vec4(0.0, 0.0, 0.0, 0.0);

	vec2 sduv = vec2(-FRADIUS * texelw, -FRADIUS * texelh);
	vec2 duv = sduv;

	for (int i = -RADIUS; i <= RADIUS; i++) {
		for (int j = -RADIUS; j <= RADIUS; j++) {
			pCol += texture2D(tex, fTex + duv);
			w += 1.0;
			duv.x += texelw;
		}
		duv.x = sduv.x;
		duv.y += texelh;
	}

	pCol /= w;
}