#version 330

#define SAMPLE_NUM 16
#define FSAMPLE_NUM 16.0

in vec2 fTex;
layout (location = 0) out vec4 pCol;

const vec3 samplePoint[SAMPLE_NUM] = 
	vec3[SAMPLE_NUM](
		vec3(-0.73105, -0.123905, 0.603997),
		vec3(-0.644142, 0.0149198, 0.923938),
		vec3(-0.561841, -0.0872364, 0.564048),
		vec3(-0.329838, -0.553394, 0.331065),
		vec3(-0.226658, 0.025881, 0.252524),
		vec3(-0.202701, 0.318089, 0.193107),
		vec3(-0.0775235, -0.57199, 0.0573087),
		vec3(0.174895, 0.781756, 0.69674),
		vec3(0.421993, 0.513071, 0.0201336),
		vec3(0.459571, 0.630715, 0.0506995),
		vec3(0.555465, 0.109432, 0.030112),
		vec3(-0.868982, -0.415858, 0.0868412),
		vec3(-0.580376, 0.460583, 0.2247),
		vec3(-0.388384, 0.404592, 0.395835),
		vec3(-0.269678, 0.087303, 0.195931),
		vec3(-0.157603, -0.265732, 0.499082)
	);

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D noise;

uniform float sampleRadius;
uniform float distLimit;
uniform float correctionThreshold;
uniform float correctionIntensity;

void main() {
	vec3 pos = texture2D(position, fTex).xyz;

	vec3 snorm = vec3(-1.0, 0.0, 0.0);
	vec3 norm = texture2D(normal, fTex).xyz;
	vec3 tang = normalize(cross(norm, snorm));
	vec3 bita = cross(norm, tang);
	mat3 tbn = mat3(tang, bita, norm);
	
	float alpha = 0.0;

	for (int i = 0; i < SAMPLE_NUM; i++) {
		vec3 dpos, spos;
		vec2 duv;
		dpos = tbn * samplePoint[i] * sampleRadius;
		spos = pos + dpos;
		duv = dpos.xy / -spos.z * 2.0;

		vec3 pos2 = texture2D(position, fTex + duv).xyz;

		if (pos2.z > spos.z && pos2.z - spos.z < distLimit)
			alpha += 1.0; 
	}

	alpha /= FSAMPLE_NUM;
	alpha = max(0.0, alpha - correctionThreshold);
	alpha /= 1.0 - correctionThreshold;
	alpha = min(alpha * correctionIntensity, 1.0);
	pCol = vec4(0.0, 0.0, 0.0, alpha);
}