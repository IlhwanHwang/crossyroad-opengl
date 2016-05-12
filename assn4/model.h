//
// BetterCarryingEachOther 2016.04.01
// model structure
//

#pragma once

#include <vector>
#include <GL/glew.h>

#include "vec.h"

using namespace std;

struct vertex {
	vec3 pos;
	vec2 tex;
	vec3 norm;

	vertex() {}

	vertex(const vec3 &pos, const vec2 &tex, const vec3 &norm)
		: pos(pos), tex(tex), norm(norm) {}
};

class Model {
private:
	GLuint buffer;
	GLuint size;
	vector<vertex> vertices;

	static GLuint fpCanonical;

public:
	static void init();
	static void drawFramePassCanonical();

	Model();

	void addBox(vec3 pos1, vec3 pos2);
	void addPoint(vec3 pos, vec2 tex, vec3 norm);

	void load(const char* fn);
	void load(const char* fn, const char* group);
	void generate();
	void draw();
};