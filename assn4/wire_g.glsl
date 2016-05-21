#version 330

layout (triangles) in;
layout (line_strip, max_vertices = 4) out;

in vec4 gPosEye[];
in vec3 gNorm[];
out vec4 fPosEye;
out vec3 fNorm;

void main() {
	for (int i = 0; i < 4; i++) {
		int j = i;
		if (i == 3)
			j = 0;

		gl_Position = gl_in[j].gl_Position;
		fPosEye = gPosEye[j];
		fNorm = gNorm[j];
		EmitVertex();
	}
    EndPrimitive();
}