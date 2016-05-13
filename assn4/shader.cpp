//
// BetterCarryingEachOther 2016.04.01
// shader management
//

#include <GL/glew.h>

#include "InitShader.h"
#include "shader.h"
#include "mat.h"
#include "debug.h"

GLuint Shader::shdFramePass;
GLuint Shader::shdFog;
PhysicalShader Shader::pshader[PSHADER_NUM];
int Shader::pshaderCurrent = 0;
mat4 Shader::modelViewCurrent;
stack<mat4> Shader::modelViewStack;
vector<vec4> Shader::lightPositions;
vector<vec4> Shader::lightColors;
int Shader::lightCount = 0;

void PhysicalShader::init(const char* fv, const char* fg, const char* ff) {
	program = glCreateProgram();
	if (fv != NULL)
		loadShader(program, GL_VERTEX_SHADER, fv);
	if (fg != NULL)
		loadShader(program, GL_GEOMETRY_SHADER, fg);
	if (ff != NULL)
		loadShader(program, GL_FRAGMENT_SHADER, ff);
	linkProgram(program);

	modelview = glGetUniformLocation(program, "modelview");
	projection = glGetUniformLocation(program, "projection");
	
	lightAmbient = glGetUniformLocation(program, "lightAmbient");
	lightCount = glGetUniformLocation(program, "lightCount");
	lightColor = glGetUniformLocation(program, "lightColor");
	lightPosition = glGetUniformLocation(program, "lightPosition");
	lightEye = glGetUniformLocation(program, "lightEye");
	specularPower = glGetUniformLocation(program, "specularPower");
	specularLightness = glGetUniformLocation(program, "specularLightness");

	glUniform1i(glGetUniformLocation(program, "tex"), 0);
	uvOffset = glGetUniformLocation(program, "uvOffset");
}

void PhysicalShader::setLights(int count, GLfloat* positions, GLfloat* colors) {
	glUseProgram(program);
	glUniform1i(lightCount, count);
	glUniform4fv(lightPosition, count, positions);
	glUniform4fv(lightColor, count, colors);
}

void PhysicalShader::setEye(vec4& eye) {
	glUseProgram(program);
	glUniform4fv(lightEye, 1, eye);
}

void PhysicalShader::setAmbient(vec4& color) {
	glUseProgram(program);
	glUniform4fv(lightAmbient, 1, color);
}

void PhysicalShader::setModelView(mat4& mat) {
	glUseProgram(program);
	glUniformMatrix4fv(modelview, 1, GL_TRUE, mat);
}

void PhysicalShader::setProjection(mat4& mat) {
	glUseProgram(program);
	glUniformMatrix4fv(projection, 1, GL_TRUE, mat);
}

void PhysicalShader::setSpecular(float s) {
	glUseProgram(program);
	glUniform1f(specularPower, powf(16.0, s));
	glUniform1f(specularLightness, s);
}

void PhysicalShader::setUVOffset(vec2& uv) {
	glUseProgram(program);
	glUniform2fv(uvOffset, 1, uv);
}

void Shader::init() {
	pshader[0].init("flat_v.glsl", "flat_g.glsl", "flat_f.glsl");
	pshader[1].init("gouraud_v.glsl", NULL, "gouraud_f.glsl");
	pshader[2].init("phong_v.glsl", NULL, "phong_f.glsl");
	pshader[3].init("wire_v.glsl", "wire_g.glsl", "wire_f.glsl");

	mat4 ident;
	modelViewStack.push(ident);

	shdFramePass = glCreateProgram();
	loadShader(shdFramePass, GL_VERTEX_SHADER, "framepass_v.glsl");
	loadShader(shdFramePass, GL_FRAGMENT_SHADER, "framepass_f.glsl");
	linkProgram(shdFramePass);
	glUniform1i(glGetUniformLocation(shdFramePass, "tex"), 0);

	shdFog = glCreateProgram();
	loadShader(shdFog, GL_VERTEX_SHADER, "fog_v.glsl");
	loadShader(shdFog, GL_FRAGMENT_SHADER, "fog_f.glsl");
	linkProgram(shdFog);
	glUniform1i(glGetUniformLocation(shdFog, "color"), 0);
	glUniform1i(glGetUniformLocation(shdFog, "depth"), 1);
	glUniform1f(glGetUniformLocation(shdFog, "fogRate"), 0.5);
	glUniform4fv(glGetUniformLocation(shdFog, "fogColor"), 1, vec4(0.8, 0.9, 1.0, 1.0));
	glUniform1f(glGetUniformLocation(shdFog, "zNear"), 10.0);
	glUniform1f(glGetUniformLocation(shdFog, "zFar"), 1000.0);

	lightCount = 0;
}

void Shader::pop() {
	modelViewCurrent = modelViewStack.top();
	modelViewStack.pop();
}

void Shader::push() {
	modelViewStack.push(modelViewCurrent);
}

void Shader::lightPush(vec4& position, vec4& color) {
	lightCount++;
	lightPositions.push_back(position);
	lightColors.push_back(color);
}

void Shader::lightApply() {
	if (lightCount > 0)
		pshader[pshaderCurrent].setLights(lightCount, lightPositions[0], lightColors[0]);
	else
		pshader[pshaderCurrent].setLights(lightCount, NULL, NULL);
}

void Shader::lightClear() {
	lightCount = 0;
	lightPositions.clear();
	lightColors.clear();
}