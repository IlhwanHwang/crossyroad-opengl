//
// BetterCarryingEachOther 2016.04.01
// shader management
//

#pragma once

#include <GL/glew.h>
#include <stack>

#include "mat.h"

using namespace std;

class Shader {
public:
	enum mode { MODE_DEFAULT };

private:
	class Default {
	public:
		static GLuint Projection;
		static GLuint ModelView;
		static GLuint lightAmbient;
		static GLuint lightVector;
		static GLuint vPos;
		static GLuint vTex;
		static GLuint vCol;
		static GLuint vNorm;
	};

	static GLuint shdDefault;
	static enum mode shdMode;

	static mat4 modelViewCurrent;
	static stack<mat4> modelViewStack;

public:
	static void init();

	static void useDefault();

	static void translate(vec3 pos);
	static void rotateX(float a);
	static void rotateY(float a);
	static void rotateZ(float a);
	static void scale(vec3 sv);

	static void pop();
	static void push();

	static enum mode getMode();
	static GLuint getProjection();
	static GLuint getModelView();
	static GLuint getvPos();
	static GLuint getvTex();
	static GLuint getvCol();
	static GLuint getvNorm();
};