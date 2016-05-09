//
// BetterCarryingEachOther 2016.04.01
// shader management
//

#include <GL/glew.h>

#include "InitShader.h"
#include "shader.h"
#include "mat.h"
#include "model.h"
#include "view.h"

GLuint Shader::Default::Projection;
GLuint Shader::Default::ModelView;
GLuint Shader::shdDefault;
GLuint Shader::shdFramePass;
GLuint Shader::shdWire;

mat4 Shader::modelViewCurrent;
stack<mat4> Shader::modelViewStack;

void Shader::init() {
	shdDefault = glCreateProgram();
	loadShader(shdDefault, GL_VERTEX_SHADER, "deferred_v.glsl");
	loadShader(shdDefault, GL_FRAGMENT_SHADER, "deferred_f.glsl");
	linkProgram(shdDefault);

	Default::ModelView = glGetUniformLocation(shdDefault, "ModelView");
	Default::Projection = glGetUniformLocation(shdDefault, "Projection");

	glUniform1i(glGetUniformLocation(shdDefault, "tex"), 0);
	glUniform4f(glGetUniformLocation(shdDefault, "fog"), 0.5, 0.75, 1.0, 1.0);
	glUniform1f(glGetUniformLocation(shdDefault, "fograte"), 0.5);
	glUniform1f(glGetUniformLocation(shdDefault, "zfar"), View::getZfar());

	glUseProgram(shdDefault);

	mat4 ident;
	modelViewStack.push(ident);

	shdFramePass = glCreateProgram();
	loadShader(shdFramePass, GL_VERTEX_SHADER, "framepass_v.glsl");
	loadShader(shdFramePass, GL_FRAGMENT_SHADER, "framepass_f.glsl");
	linkProgram(shdFramePass);
	glUniform1i(glGetUniformLocation(shdFramePass, "tex"), 0);

	shdWire = glCreateProgram();
	loadShader(shdWire, GL_VERTEX_SHADER, "wire_v.glsl");
	loadShader(shdWire, GL_GEOMETRY_SHADER, "wire_g.glsl");
	loadShader(shdWire, GL_FRAGMENT_SHADER, "wire_f.glsl");
	linkProgram(shdWire);
}

void Shader::pop() {
	modelViewStack.pop();
	modelViewCurrent = modelViewStack.top();
}

void Shader::push() {
	modelViewStack.push(modelViewCurrent);
	glUniformMatrix4fv(Default::ModelView, 1, GL_TRUE, modelViewCurrent);
}