//
// BetterCarryingEachOther 2016.05.09
// framebuffer class
//

#pragma once

#include <GL/glew.h>

#include "view.h"

class Framebuffer {
protected:
	GLuint fb, diffuse, position, normal, dep;
	GLsizei w, h;
	void echostatus();

public:
	Framebuffer(GLsizei w, GLsizei h) : w(w), h(h) {};

	void generate();
	void bind();
	void unbind();
	void bindDiffuse() { glBindTexture(GL_TEXTURE_2D, diffuse); };
	void bindPosition() { glBindTexture(GL_TEXTURE_2D, position); };
	void bindNormal() { glBindTexture(GL_TEXTURE_2D, normal); };
	void bindDepth() { glBindTexture(GL_TEXTURE_2D, dep); };
};

class FramebufferSingle : public Framebuffer {
public:
	FramebufferSingle(GLsizei w, GLsizei h) : Framebuffer(w, h) {}

	void generate();
};