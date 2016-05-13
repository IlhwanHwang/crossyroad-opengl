//
// BetterCarryingEachOther 2016.04.01
// shader management
//

#pragma once

#include <GL/glew.h>
#include <stack>
#include <vector>

#include "mat.h"

#define PSHADER_NUM 4

using namespace std;

class PhysicalShader {
private:
	GLuint program;

	GLuint projection;
	GLuint modelview;

	GLuint lightAmbient;
	GLuint lightCount;
	GLuint lightColor;
	GLuint lightPosition;
	GLuint lightEye;
	GLuint specularPower;
	GLuint specularLightness;

	GLuint uvOffset;

public:
	void init(const char* fv, const char* fg, const char* ff);
	void use() { glUseProgram(program); }
	GLuint getProjection() { return projection; }
	GLuint getModelView() { return modelview; }
	void setLights(int count, GLfloat* positions, GLfloat* colors);
	void setEye(vec4& eye);
	void setAmbient(vec4& color);
	void setModelView(mat4& mat);
	void setProjection(mat4& mat);
	void setSpecular(float s);
	void setUVOffset(vec2& uv);

	GLuint getLightAmbient() { return lightAmbient; }
};

class Shader {
private:
	static GLuint shdFramePass;
	static GLuint shdFog;

	static PhysicalShader pshader[PSHADER_NUM];
	static int pshaderCurrent;
	static mat4 modelViewCurrent;
	static stack<mat4> modelViewStack;
	static vector<vec4> lightPositions;
	static vector<vec4> lightColors;
	static int lightCount;

public:
	static void init();

	static void usePhysicalShader() { pshader[pshaderCurrent].use(); }
	static void switchPhysicalShader() { pshaderCurrent = (pshaderCurrent + 1) % PSHADER_NUM; }
	static void useFramePass() { glUseProgram(shdFramePass); }
	static void useFog() { glUseProgram(shdFog); }

	static void translate(vec3 pos) { modelViewCurrent *= Matrix::Translate(pos); }
	static void rotateX(float a) { modelViewCurrent *= Matrix::RotateX(a); }
	static void rotateY(float a) { modelViewCurrent *= Matrix::RotateY(a); }
	static void rotateZ(float a) { modelViewCurrent *= Matrix::RotateZ(a); }
	static void scale(vec3 sv) { modelViewCurrent *= Matrix::Scale(sv); }

	static void pop();
	static void push();
	static void apply() { pshader[pshaderCurrent].setModelView(modelViewCurrent); }

	static void lightPush(vec4& position, vec4& color);
	static void lightApply();
	static void lightClear();

	static PhysicalShader& getPhysicalShader() { return pshader[pshaderCurrent]; }
};