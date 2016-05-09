#version 150

in vec4 vPos;
in vec2 vTex;
in vec4 vCol;
in vec4 vNorm;
out vec2 pTex;
out vec4 pCol;
out float pDepth;

uniform mat4 ModelView;
uniform mat4 Projection;

uniform float lightAmbient;
uniform vec3 lightVector;

float lerp(float a, float b, float x) {
	return a * (1.0 - x) + b * x;
}

float ip(vec3 a, vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec4 normalize(vec4 v) {
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return v / length;
}

void main()
{
    gl_Position = Projection * ModelView * vPos / vPos.w;
	pDepth = gl_Position.w;

	vec4 mNorm = normalize(ModelView * vec4(vNorm.xyz, 0.0));

	float light;
	light = -ip(mNorm.xyz, lightVector);

	if (light > 0.0)
		pCol = vec4(vCol.rgb * lerp(light, 1.0, lightAmbient), vCol.a);
	else
		pCol = vec4(vCol.rgb * lightAmbient, vCol.a);

	pTex = vTex;
}
