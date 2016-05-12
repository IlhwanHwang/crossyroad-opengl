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

GLuint Model::fpCanonical;

void Model::init() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vector<vec2> data;
	data.push_back(vec2(-1.0, -1.0));
	data.push_back(vec2(0.0, 0.0));
	data.push_back(vec2(1.0, -1.0));
	data.push_back(vec2(1.0, 0.0));
	data.push_back(vec2(-1.0, 1.0));
	data.push_back(vec2(0.0, 1.0));
	data.push_back(vec2(1.0, 1.0));
	data.push_back(vec2(1.0, 1.0));

	glGenBuffers(1, &fpCanonical);
	glBindBuffer(GL_ARRAY_BUFFER, fpCanonical);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * data.size(), &data[0], GL_STATIC_DRAW);
	data.clear();
}

void Model::drawFramePassCanonical() {
	glBindBuffer(GL_ARRAY_BUFFER, fpCanonical);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2) * 2, (void*)sizeof(vec2));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

Model::Model() {}

void Model::addBox(vec3 pos1, vec3 pos2) {
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

	addPoint(pos111, lt, nl);
	addPoint(pos112, rt, nl);
	addPoint(pos121, lb, nl);
	addPoint(pos121, lb, nl);
	addPoint(pos112, rt, nl);
	addPoint(pos122, rb, nl);

	addPoint(pos112, lt, nu);
	addPoint(pos212, rt, nu);
	addPoint(pos122, lb, nu);
	addPoint(pos122, lb, nu);
	addPoint(pos212, rt, nu);
	addPoint(pos222, rb, nu);

	addPoint(pos212, lt, nr);
	addPoint(pos211, rt, nr);
	addPoint(pos222, lb, nr);
	addPoint(pos222, lb, nr);
	addPoint(pos211, rt, nr);
	addPoint(pos221, rb, nr);

	addPoint(pos211, lt, nd);
	addPoint(pos111, rt, nd);
	addPoint(pos221, lb, nd);
	addPoint(pos221, lb, nd);
	addPoint(pos111, rt, nd);
	addPoint(pos121, rb, nd);

	addPoint(pos211, lt, nb);
	addPoint(pos212, rt, nb);
	addPoint(pos111, lb, nb);
	addPoint(pos111, lb, nb);
	addPoint(pos212, rt, nb);
	addPoint(pos112, rb, nb);

	addPoint(pos221, lt, nf);
	addPoint(pos121, rt, nf);
	addPoint(pos222, lb, nf);
	addPoint(pos222, lb, nf);
	addPoint(pos121, rt, nf);
	addPoint(pos122, rb, nf);
}

void Model::addPoint(vec3 pos, vec2 tex, vec3 norm) {
	vertices.push_back(vertex(pos, tex, norm));
}

void Model::load(const char* fn) {
	load(fn, NULL);
}

void Model::load(const char* fn, const char* group) {
	ifstream f(fn);

	vector<vec3> v;
	vector<vec2> vt;
	vector<vec3> vn;
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
			if (group != NULL) {
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

			vertex v1 = vertex(v[stoi(p1[0])], vt[stoi(p1[1])], vn[stoi(p1[2])]);
			vertex v2 = vertex(v[stoi(p2[0])], vt[stoi(p2[1])], vn[stoi(p2[2])]);
			vertex v3 = vertex(v[stoi(p3[0])], vt[stoi(p3[1])], vn[stoi(p3[2])]);
			vertex v4;
			if (quad)
				v4 = vertex(v[stoi(p4[0])], vt[stoi(p4[1])], vn[stoi(p4[2])]);

			vertices.push_back(v1);
			vertices.push_back(v2);
			vertices.push_back(v3);
			if (quad) {
				vertices.push_back(v3);
				vertices.push_back(v4);
				vertices.push_back(v1);
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

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid *)(sizeof(vec3) + sizeof(vec2)));

	glDrawArrays(GL_TRIANGLES, 0, size);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}