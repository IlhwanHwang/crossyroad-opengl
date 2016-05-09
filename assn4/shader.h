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
private:
	class Default {
	public:
		static GLuint Projection;
		static GLuint ModelView;
	};

	class FramePass {
	};

	class Wire {
	};

	static GLuint shdDefault;
	static GLuint shdFramePass;
	static GLuint shdWire;

	static mat4 modelViewCurrent;
	static stack<mat4> modelViewStack;

public:
	static void init();

	static void useDefault() { glUseProgram(shdDefault); };
	static void useFramePass() { glUseProgram(shdFramePass); };
	static void useWire() { glUseProgram(shdWire); };

	static void translate(vec3 pos) { modelViewCurrent *= Matrix::Translate(pos); };
	static void rotateX(float a) { modelViewCurrent *= Matrix::RotateX(a); };
	static void rotateY(float a) { modelViewCurrent *= Matrix::RotateY(a); };
	static void rotateZ(float a) { modelViewCurrent *= Matrix::RotateZ(a); };
	static void scale(vec3 sv) { modelViewCurrent *= Matrix::Scale(sv); };

	static void pop();
	static void push();

	static GLuint getProjection() { return Default::Projection; };
	static GLuint getModelView() { return Default::ModelView; };
};