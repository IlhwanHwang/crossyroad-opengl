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
GLuint Shader::shdSSAO;
GLuint Shader::shdBlur;
PhysicalShader Shader::pshader[PSHADER_NUM];
PhysicalShader Shader::hide;
int Shader::pshaderCurrent = 0;
mat4 Shader::modelViewCurrent;
stack<mat4> Shader::modelViewStack;
vector<vec4> Shader::lightPositions;
vector<vec4> Shader::lightColors;
int Shader::lightCount = 0;
GLuint Shader::fogColor;
bool Shader::hidePass = false;

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
	eyeview = glGetUniformLocation(program, "eyeview");
	projection = glGetUniformLocation(program, "projection");
	
	lightAmbient = glGetUniformLocation(program, "lightAmbient");
	lightCount = glGetUniformLocation(program, "lightCount");
	lightColor = glGetUniformLocation(program, "lightColor");
	lightPosition = glGetUniformLocation(program, "lightPosition");
	lightEye = glGetUniformLocation(program, "lightEye");
	specularPower = glGetUniformLocation(program, "specularPower");
	specularLightness = glGetUniformLocation(program, "specularLightness");

	glUniform1i(glGetUniformLocation(program, "color"), 0);
	glUniform1i(glGetUniformLocation(program, "normal"), 1);
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

void PhysicalShader::setEyeView(mat4& mat) {
	glUseProgram(program);
	glUniformMatrix4fv(eyeview, 1, GL_TRUE, mat);
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
	pshader[2].init("phong_v.glsl", "phong_g.glsl", "phong_f.glsl");
	pshader[3].init("wire_v.glsl", "wire_g.glsl", "wire_f.glsl");
	hide.init("hide_v.glsl", NULL, "hide_f.glsl");

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
	glUniform1i(glGetUniformLocation(shdFog, "depth"), 0);
	glUniform1f(glGetUniformLocation(shdFog, "fogRate"), 0.5);
	fogColor = glGetUniformLocation(shdFog, "fogColor");
	glUniform1f(glGetUniformLocation(shdFog, "zNear"), 10.0);
	glUniform1f(glGetUniformLocation(shdFog, "zFar"), 1000.0);

	shdSSAO = glCreateProgram();
	loadShader(shdSSAO, GL_VERTEX_SHADER, "ssao_v.glsl");
	loadShader(shdSSAO, GL_FRAGMENT_SHADER, "ssao_f.glsl");
	linkProgram(shdSSAO);
	glUniform1i(glGetUniformLocation(shdSSAO, "position"), 0);
	glUniform1i(glGetUniformLocation(shdSSAO, "normal"), 1);
	glUniform1i(glGetUniformLocation(shdSSAO, "noise"), 2);
	glUniform1f(glGetUniformLocation(shdSSAO, "sampleRadius"), 8.0);
	glUniform1f(glGetUniformLocation(shdSSAO, "distLimit"), 32.0);
	glUniform1f(glGetUniformLocation(shdSSAO, "correctionThreshold"), 0.2);
	glUniform1f(glGetUniformLocation(shdSSAO, "correctionIntensity"), 1.7);

	shdBlur = glCreateProgram();
	loadShader(shdBlur, GL_VERTEX_SHADER, "blur_v.glsl");
	loadShader(shdBlur, GL_FRAGMENT_SHADER, "blur_f.glsl");
	linkProgram(shdBlur);
	glUniform1i(glGetUniformLocation(shdBlur, "tex"), 0);
	glUniform1f(glGetUniformLocation(shdBlur, "texelw"), 1.0 / 768.0);
	glUniform1f(glGetUniformLocation(shdBlur, "texelh"), 1.0 / 768.0);

	lightCount = 0;
	hidePass = false;
}

void Shader::pop() {
	modelViewCurrent = modelViewStack.top();
	modelViewStack.pop();
	getPhysicalShader().setUVOffset(vec2(0.0, 0.0));
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

void Shader::fogSetColor(vec4& color) {
	glUseProgram(shdFog);
	glUniform4fv(fogColor, 1, color);
}

PhysicalShader& Shader::getPhysicalShader() {
	if (isWire()) {
		if (hidePass)
			return hide;
		else
			return pshader[pshaderCurrent];
	}
	else {
		return pshader[pshaderCurrent];
	}
}