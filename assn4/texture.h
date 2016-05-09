//
// BetterCarryingEachOther 2016.04.07
// texture management unit
//

#pragma once

#include <GL/glut.h>

class Texture {
private:
	unsigned w, h;
	GLuint buf;

public:
	void load(const char* fn);
	void bind();
};