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

GLuint Shader::Default::vPos;
GLuint Shader::Default::vTex;
GLuint Shader::Default::vCol;
GLuint Shader::Default::vNorm;
GLuint Shader::Default::Projection;
GLuint Shader::Default::ModelView;
GLuint Shader::Default::lightAmbient;
GLuint Shader::Default::lightVector;

GLuint Shader::shdDefault;
Shader::mode Shader::shdMode;

mat4 Shader::modelViewCurrent;
stack<mat4> Shader::modelViewStack;

void Shader::init() {
	shdDefault = Angel::InitShader("v_default.glsl", "f_default.glsl");

	Default::vPos = glGetAttribLocation(shdDefault, "vPos");
	glEnableVertexAttribArray(Default::vPos);
	Default::vTex = glGetAttribLocation(shdDefault, "vTex");
	glEnableVertexAttribArray(Default::vTex);
	Default::vCol = glGetAttribLocation(shdDefault, "vCol");
	glEnableVertexAttribArray(Default::vCol);
	Default::vNorm = glGetAttribLocation(shdDefault, "vNorm");
	glEnableVertexAttribArray(Default::vNorm);

	Default::ModelView = glGetUniformLocation(shdDefault, "ModelView");
	Default::Projection = glGetUniformLocation(shdDefault, "Projection");
	Default::lightAmbient = glGetUniformLocation(shdDefault, "lightAmbient");
	Default::lightVector = glGetUniformLocation(shdDefault, "lightVector");

	glUniform1f(Default::lightAmbient, 0.5);
	vec3 lv = normalize(vec3(0.5, 0.0, -1.0));
	glUniform3f(Default::lightVector, lv.x, lv.y, lv.z);
	glUniform1i(glGetUniformLocation(shdDefault, "tex"), 0);

	glUniform4f(glGetUniformLocation(shdDefault, "fog"), 
		Color::sky.x, Color::sky.y, Color::sky.z, 1.0);
	glUniform1f(glGetUniformLocation(shdDefault, "fograte"), 0.5);

	glUniform1f(glGetUniformLocation(shdDefault, "zfar"), View::getZfar());

	shdMode = MODE_DEFAULT;
	glUseProgram(shdDefault);

	mat4 ident;
	modelViewStack.push(ident);
}

void Shader::useDefault() {
	shdMode = MODE_DEFAULT;
	glUseProgram(shdDefault);
}

void Shader::translate(vec3 pos) {
	modelViewCurrent *= Matrix::Translate(pos);
}

void Shader::rotateX(float a) {
	modelViewCurrent *= Matrix::RotateX(a);
}

void Shader::rotateY(float a) {
	modelViewCurrent *= Matrix::RotateY(a);
}

void Shader::rotateZ(float a) {
	modelViewCurrent *= Matrix::RotateZ(a);
}

void Shader::scale(vec3 sv) {
	modelViewCurrent *= Matrix::Scale(sv);
}

void Shader::pop() {
	modelViewStack.pop();
	modelViewCurrent = modelViewStack.top();
}

void Shader::push() {
	modelViewStack.push(modelViewCurrent);
	glUniformMatrix4fv(Default::ModelView, 1, GL_TRUE, modelViewCurrent);
}

Shader::mode Shader::getMode() {
	return shdMode;
}

GLuint Shader::getProjection() {
	return Default::Projection;
}

GLuint Shader::getModelView() {
	return Default::ModelView;
}

GLuint Shader::getvPos() {
	switch (shdMode) {
	case MODE_DEFAULT: return Default::vPos;
	}
}

GLuint Shader::getvTex() {
	switch (shdMode) {
	case MODE_DEFAULT: return Default::vTex;
	}
}

GLuint Shader::getvCol() {
	return Default::vCol;
}

GLuint Shader::getvNorm() {
	return Default::vNorm;
}
