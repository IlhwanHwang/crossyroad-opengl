//
// BetterCarryingEachOther 2016.03.17
// viewing area management
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

#include "game.h"
#include "view.h"
#include "utility.h"
#include "mat.h"
#include "shader.h"
#include "key.h"

#include "debug.h"

float View::x = 0.0;
float View::y = 0.0;
float View::width = 768.0;
float View::height = 768.0;
float View::tx = 0.0;
float View::ty = 0.0;

float View::offsetTop = View::height * 0.55;
float View::offsetLeft = View::width * 0.5;

float View::zfar = 1000.0;
float View::znear = 1.0;
float View::aspect = View::width / View::height;
float View::dist = 400.0;

float View::viewDir = 0.0;
View::mode View::viewMode = View::VIEW_FRONT;

void View::init() {
	x = 0.0;
	y = -Game::getGrid() * 5.0;
	tx = View::width * 0.5;
	ty = 0.0;
}

void View::setViewAt(float _x, float _y) {
	tx = _x;
	ty = _y;
}

void View::setAspect(float asp) {
	aspect = asp;
}

void View::update() {
	if (Key::keyCheckPressed('q')) {
		switch (viewMode) {
		case VIEW_FRONT: viewMode = VIEW_BACK; break;
		case VIEW_BACK: viewMode = VIEW_BIRD; break;
		case VIEW_BIRD: viewMode = VIEW_FRONT; break;
		}
	}

	x = flerp(tx, x, 0.9);
	y = flerp(ty, y, 0.9);

	mat4 Project;
	vec4 eye, at, up;

	switch (viewMode) {
	case VIEW_FRONT:
		eye = vec4(x, y, Game::getGrid() / 2.0, 1.0);
		at = eye + vec4(cosf(degToRad(viewDir)), sinf(degToRad(viewDir)), 0.0, 0.0);
		up = vec4(0.0, 0.0, 1.0, 0.0);

		Project *= Matrix::Perspective(45.0, aspect, znear, zfar);
		Project *= Matrix::LookAt(eye, at, up);
		break;

	case VIEW_BACK:
		at = vec4(x, y, Game::getGrid() / 2.0, 1.0);
		eye = at - vec4(cosf(degToRad(viewDir)), sinf(degToRad(viewDir)), 0.0, 0.0) * dist;
		eye += vec4(0.0, 0.0, dist * 0.5, 0.0);
		up = vec4(0.0, 0.0, 1.0, 0.0);

		Project *= Matrix::Perspective(45.0, aspect, znear, zfar);
		Project *= Matrix::LookAt(eye, at, up);
		break;

	case VIEW_BIRD:
		Project *= Matrix::Ortho(-height / 3.0 * aspect, height / 3.0 * aspect, -height / 3.0, height / 3.0, -height, height);
		eye = vec4(0.0, y, 0.0, 1.0);
		at = vec4(0.0, y, -1.0, 1.0);
		up = vec4(0.0, 1.0, 0.0, 0.0);
		Project *= Matrix::LookAt(eye, at, up);
		break;
	}

	Shader::getPhysicalShader().setProjection(Project);
	Shader::getPhysicalShader().setEye(eye);
}

void View::setViewDir(float dir) {
	viewDir = dir;
}

float View::getWidth() {
	return width;
}

float View::getHeight() {
	return height;
}

float View::getX() {
	return x;
}

float View::getY() {
	return y;
}

float View::getZfar() {
	return zfar;
}

float View::getZnear() {
	return znear;
}

float View::getViewDir() {
	return viewDir;
}

View::mode View::getViewMode() {
	return viewMode;
}