//
// BetterCarryingEachOther 2016.04.07
// texture management unit
//

#pragma once

#include <GL/freeglut.h>

class Texture {
private:
	unsigned w, h;
	GLuint buf;
	GLenum type;

public:
	void load(const char* fn, GLenum type);
	void bind();
	void nbind();
};