//
// BetterCarryingEachOther 2016.05.09
// debug module
//

#include "debug.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

void errorecho(const char* append) {
	cout << append << ": ";
	switch (glGetError()) {
	case GL_NO_ERROR:
		cout << "No error" << endl;
		break;
	case GL_INVALID_ENUM:
		cout << "Invaild enumerator" << endl;
		break;
	case GL_INVALID_VALUE:
		cout << "Invalid value" << endl;
		break;
	case GL_INVALID_OPERATION:
		cout << "Invalid operation" << endl;
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		cout << "Invalid framebuffer operation" << endl;
		break;
	case GL_OUT_OF_MEMORY:
		cout << "Out of memory" << endl;
		break;
	}
}

void errorecho() {
	errorecho("Error");
}