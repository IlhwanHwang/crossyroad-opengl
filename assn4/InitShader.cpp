//
// BetterCarryingEachOther 2016.05.09
// refactored initshader module (original initshader by Angel)
//

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "debug.h"

using namespace std;

void loadShader(GLuint program, GLenum type, const char* fn) {
	string buf;
	string source;
	ifstream f(fn);

	if (!f.is_open()) {
		cerr << "Failed to read " << fn << endl;
		exit(EXIT_FAILURE);
	}

	while (!f.eof()) {
		getline(f, buf);
		source += buf + "\n";
	}

	const char* csource = source.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const GLchar**)&csource, NULL);
	glCompileShader(shader);

	GLint  compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		cerr << fn << " failed to compile:" << endl;
		GLint  logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetShaderInfoLog(shader, logSize, NULL, logMsg);
		cerr << logMsg << endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	glAttachShader(program, shader);
}

void linkProgram(GLuint program) {
	glLinkProgram(program);

	GLint  linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		cerr << "Shader program failed to link" << endl;
		GLint  logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		cerr << logMsg << endl;
		delete[] logMsg;

		exit(EXIT_FAILURE);
	}

	glUseProgram(program);
}