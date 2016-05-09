//
// BetterCarryingEachOther 2016.04.01
// model structure
//

#include <GL/glew.h>
#include <fstream>
#include <string>

#include "resource.h"
#include "model.h"
#include "shader.h"
#include "utility.h"

const vec3 Color::red = vec3(1.0, 0.0, 0.0);
const vec3 Color::darkred = vec3(0.5, 0.0, 0.0);
const vec3 Color::yellow = vec3(1.0, 1.0, 0.0);
const vec3 Color::black = vec3(0.0, 0.0, 0.0);
const vec3 Color::white = vec3(1.0, 1.0, 1.0);
const vec3 Color::gray = vec3(0.5, 0.5, 0.5);
const vec3 Color::grass = vec3(0.3, 0.7, 0.3);
const vec3 Color::darkgrass = vec3(0.2, 0.4, 0.2);
const vec3 Color::water = vec3(0.3, 0.7, 1.0);
const vec3 Color::stem = vec3(0.5, 0.25, 0.0);
const vec3 Color::pink = vec3(1.0, 0.5, 1.0);
const vec3 Color::sky = vec3(0.65, 0.8, 0.95);

vec3 Color::stoc(string& str) {
	if (str.compare("red") == 0)
		return red;
	if (str.compare("yellow") == 0)
		return yellow;
	if (str.compare("black") == 0)
		return black;
	if (str.compare("white") == 0)
		return white;
	if (str.compare("gray") == 0)
		return gray;
	if (str.compare("grass") == 0)
		return grass;
	if (str.compare("darkgrass") == 0)
		return darkgrass;
	if (str.compare("water") == 0)
		return water;
	if (str.compare("stem") == 0)
		return stem;
	if (str.compare("pink") == 0)
		return pink;

	return vec3(1.0, 1.0, 1.0);
}

void Model::init() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

Model::Model() {
	mtype = TYPE_TRIANGLE;
}

Model::Model(enum type t) : mtype(t) {}

void Model::addRect(vec2 pos1, vec2 pos2, vec3 col) {
	vec2 pos12 = vec2(pos1.x, pos2.y);
	vec2 pos21 = vec2(pos2.x, pos1.y);

	vertices.push_back(vertex(pos1, vec2(0.0, 0.0), col, vec3(0.0, 0.0, 1.0)));
	vertices.push_back(vertex(pos21, vec2(0.0, 1.0), col, vec3(0.0, 0.0, 1.0)));
	vertices.push_back(vertex(pos12, vec2(1.0, 0.0), col, vec3(0.0, 0.0, 1.0)));
	vertices.push_back(vertex(pos21, vec2(1.0, 0.0), col, vec3(0.0, 0.0, 1.0)));
	vertices.push_back(vertex(pos12, vec2(0.0, 1.0), col, vec3(0.0, 0.0, 1.0)));
	vertices.push_back(vertex(pos2, vec2(1.0, 1.0), col, vec3(0.0, 0.0, 1.0)));
}

void Model::addBox(vec3 pos1, vec3 pos2, vec3 col) {
	vec3 pos111 = pos1;
	vec3 pos112 = vec3(pos1.x, pos1.y, pos2.z);
	vec3 pos121 = vec3(pos1.x, pos2.y, pos1.z);
	vec3 pos122 = vec3(pos1.x, pos2.y, pos2.z);
	vec3 pos211 = vec3(pos2.x, pos1.y, pos1.z);
	vec3 pos212 = vec3(pos2.x, pos1.y, pos2.z);
	vec3 pos221 = vec3(pos2.x, pos2.y, pos1.z);
	vec3 pos222 = pos2;

	vec3 nu = vec3(0.0, 0.0, 1.0);
	vec3 nd = vec3(0.0, 0.0, -1.0);
	vec3 nr = vec3(1.0, 0.0, 0.0);
	vec3 nl = vec3(-1.0, 0.0, 0.0);
	vec3 nf = vec3(0.0, 1.0, 0.0);
	vec3 nb = vec3(0.0, -1.0, 0.0);

	vec2 lt = vec2(0.0, 0.0);
	vec2 rt = vec2(1.0, 0.0);
	vec2 lb = vec2(0.0, 1.0);
	vec2 rb = vec2(1.0, 1.0);

	addPoint(pos111, lt , col, nl);
	addPoint(pos112, rt, col, nl);
	addPoint(pos121, lb, col, nl);
	addPoint(pos121, lb, col, nl);
	addPoint(pos112, rt, col, nl);
	addPoint(pos122, rb, col, nl);

	addPoint(pos112, lt, col, nu);
	addPoint(pos212, rt, col, nu);
	addPoint(pos122, lb, col, nu);
	addPoint(pos122, lb, col, nu);
	addPoint(pos212, rt, col, nu);
	addPoint(pos222, rb, col, nu);

	addPoint(pos212, lt, col, nr);
	addPoint(pos211, rt, col, nr);
	addPoint(pos222, lb, col, nr);
	addPoint(pos222, lb, col, nr);
	addPoint(pos211, rt, col, nr);
	addPoint(pos221, rb, col, nr);

	addPoint(pos211, lt, col, nd);
	addPoint(pos111, rt, col, nd);
	addPoint(pos221, lb, col, nd);
	addPoint(pos221, lb, col, nd);
	addPoint(pos111, rt, col, nd);
	addPoint(pos121, rb, col, nd);

	addPoint(pos211, lt, col, nb);
	addPoint(pos212, rt, col, nb);
	addPoint(pos111, lb, col, nb);
	addPoint(pos111, lb, col, nb);
	addPoint(pos212, rt, col, nb);
	addPoint(pos112, rb, col, nb);

	addPoint(pos221, lt, col, nf);
	addPoint(pos121, rt, col, nf);
	addPoint(pos222, lb, col, nf);
	addPoint(pos222, lb, col, nf);
	addPoint(pos121, rt, col, nf);
	addPoint(pos122, rb, col, nf);
}

void Model::addPoint(vec3 pos, vec2 tex, vec3 col, vec3 norm) {
	vertices.push_back(vertex(pos, tex, col, norm));
}

void Model::addPoint(vertex v) {
	vertices.push_back(v);
}

void Model::load(const char* fn) {
	load(fn, NULL);
}

void Model::load(const char* fn, const char* group) {
	ifstream f(fn);

	vector<vec3> v;
	vector<vec2> vt;
	vector<vec3> vn;
	vec3 col = vec3(1.0, 1.0, 1.0);
	bool skip = true;

	v.push_back(vec3(0.0, 0.0, 0.0));
	vt.push_back(vec2(0.0, 0.0));
	vn.push_back(vec3(0.0, 0.0, 0.0));

	while (!f.eof()) {
		string buf;
		getline(f, buf);

		if (buf.length() == 0)
			continue;

		vector<string> t = tokenize(buf, " ");
		string flag = t[0];

		if (flag.compare("#") == 0) {
			continue;
		}
		else if (flag.compare("v") == 0) {
			v.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		}
		else if (flag.compare("vt") == 0) {
			vt.push_back(vec2(stof(t[1]), stof(t[2])));
		}
		else if (flag.compare("vn") == 0) {
			vn.push_back(vec3(stof(t[1]), stof(t[2]), stof(t[3])));
		}
		else if (flag.compare("g") == 0) {
			if (group == NULL) {
				col = Color::stoc(t[1]);
			}
			else {
				if (skip) {
					if (string(group).compare(t[1]) == 0)
						skip = false;
					else
						continue;
				}
				else {
					break;
				}
			}
		}
		else if (flag.compare("f") == 0) {
			if (skip && group != NULL)
				continue;

			bool quad = (t.size() == 5);

			vector<string> p1 = tokenize(t[1], "/");
			vector<string> p2 = tokenize(t[2], "/");
			vector<string> p3 = tokenize(t[3], "/");
			vector<string> p4;
			if (quad)
				p4 = tokenize(t[4], "/");

			vertex v1 = vertex(v[stoi(p1[0])], vt[stoi(p1[1])], col, vn[stoi(p1[2])]);
			vertex v2 = vertex(v[stoi(p2[0])], vt[stoi(p2[1])], col, vn[stoi(p2[2])]);
			vertex v3 = vertex(v[stoi(p3[0])], vt[stoi(p3[1])], col, vn[stoi(p3[2])]);
			vertex v4;
			if (quad)
				v4 = vertex(v[stoi(p4[0])], vt[stoi(p4[1])], col, vn[stoi(p4[2])]);

			if (mtype == TYPE_TRIANGLE) {
				addPoint(v1);
				addPoint(v2);
				addPoint(v3);
				if (quad) {
					addPoint(v3);
					addPoint(v4);
					addPoint(v1);
				}
			}
			else if (mtype == TYPE_LINE) {
				addPoint(v1);
				addPoint(v2);
				addPoint(v2);
				addPoint(v3);
				addPoint(v3);
				if (quad) {
					addPoint(v4);
					addPoint(v4);
				}
				addPoint(v1);
			}
		}
	}

	f.close();

	cout << "Model: " << fn << " loaded with " << vertices.size() << " vertices" << endl;
}

void Model::generate() {
	size = vertices.size();

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	vertices.clear();
}

void Model::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(Shader::getvPos(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(Shader::getvTex(), 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3)));
	if (Shader::getMode() == Shader::MODE_DEFAULT) {
		glVertexAttribPointer(Shader::getvCol(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3) + sizeof(vec2)));
		glVertexAttribPointer(Shader::getvNorm(), 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3) + sizeof(vec2) + sizeof(vec3)));
	}
	switch (mtype) {
	case TYPE_TRIANGLE: glDrawArrays(GL_TRIANGLES, 0, size); break;
	case TYPE_LINE: glDrawArrays(GL_LINES, 0, size); break;
	}
}