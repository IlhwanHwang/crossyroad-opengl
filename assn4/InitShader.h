#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

namespace Angel {
	GLuint InitShader(const char* vShaderFile, const char* fShaderFile);
}