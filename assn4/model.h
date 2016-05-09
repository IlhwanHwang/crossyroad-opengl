//
// BetterCarryingEachOther 2016.04.01
// model structure
//

#pragma once

#include <vector>
#include <GL/glew.h>

#include "vec.h"

using namespace std;

class Color {
public:
	static const vec3 red;
	static const vec3 darkred;
	static const vec3 yellow;
	static const vec3 black;
	static const vec3 white;
	static const vec3 gray;
	static const vec3 grass;
	static const vec3 darkgrass;
	static const vec3 water;
	static const vec3 stem;
	static const vec3 pink;
	static const vec3 sky;
	static vec3 stoc(string& str);
};

struct vertex {
	vec3 pos;
	vec2 tex;
	vec3 col;
	vec3 norm;

	vertex() {}

	vertex(const vec3 &pos, const vec2 &tex, const vec3 &col, const vec3 &norm)
		: pos(pos), tex(tex), col(col), norm(norm) {}

	vertex(const vec2 &pos, const vec2 &tex, const vec3 &col, const vec3 &norm) {
		vertex(vec3(pos.x, pos.y, 0.0f), tex, col, norm);
	}
};

class Model {
public:
	enum type { TYPE_TRIANGLE, TYPE_LINE };

private:
	GLuint buffer;
	GLuint size;
	vector<vertex> vertices;
	enum type mtype;

public:
	static void init();

	Model();
	Model(enum type t);

	void addRect(vec2 pos1, vec2 pos2, vec3 col);
	void addBox(vec3 pos1, vec3 pos2, vec3 col);
	void addPoint(vec3 pos, vec2 tex, vec3 col, vec3 norm);
	void addPoint(vertex v);
	void load(const char* fn);
	void load(const char* fn, const char* group);
	void generate();
	void draw();
};