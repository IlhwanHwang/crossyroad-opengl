//
// BetterCarryingEachOther 2016.05.09
// refactored initshader module (original initshader by Angel)
//

#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

void loadShader(GLuint program, GLenum type, const char* fn);
void linkProgram(GLuint program);