#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 gTex[];
in vec4 gPos[];
in vec4 gPosEye[];
in vec3 gNorm[];

out vec2 fTex;
out vec4 fPos;
out vec4 fPosEye;
out vec3 fNorm;
out mat3 fTBN;

void main() {
	vec3 dPos1, dPos2;
	vec2 dUV1, dUV2;

	dPos1 = gPos[1].xyz - gPos[0].xyz;
	dPos2 = gPos[2].xyz - gPos[0].xyz;
	dUV1 = gTex[1] - gTex[0];
	dUV2 = gTex[2] - gTex[0];

	vec3 tangent, bitangent;

	tangent = normalize(dPos1 * dUV2.y - dPos2 * dUV1.y);
	bitangent = normalize(dPos2 * dUV1.x - dPos1 * dUV2.x);

	for (int i = 0; i < 3; i ++) {
		gl_Position = gl_in[i].gl_Position;
		fTex = gTex[i];
		fPos = gPos[i];
		fPosEye = gPosEye[i];
		fNorm = gNorm[i];
		fTBN = mat3(tangent, bitangent, gNorm[i]);
		EmitVertex();
	}
	EndPrimitive();
}