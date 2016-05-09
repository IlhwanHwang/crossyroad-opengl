//
// BetterCarryingEachOther 2016.03.11
// player class
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

#include "game.h"
#include "object.h"
#include "player.h"
#include "view.h"
#include "key.h"
#include "utility.h"
#include "deco.h"
#include "shader.h"
#include "resource.h"

float Player::xlimit = Game::getGrid() * 3.0;

float Player::getXlimit() {
	return xlimit;
}

Player::Player(Object* srnd) : Object::Object(20.0, 20.0, 10.0, 10.0) {
	this->srnd = srnd;
	dead = D_ALIVE;
	xx = 0.0;
	yy = 0.0;
	dir = 90.0;
	adir = 90.0;
	flatten = 0.0;
	ylimit = pos.y - Game::getGrid();

	name = "Player";
}

void Player::draw() const {
	if (View::getViewMode() == View::VIEW_FRONT)
		return;

	const float piPhase = aniPhase * 3.1415926;
	const float sFac = sinf(piPhase);
	const float bodyWidth = 8.0;

	Resource::Tex::goraniWhole.bind();

	Shader::translate(vec3(xx, yy, pos.z + 10.0 * sFac));
	Shader::rotateZ(adir + 180.0);
	Shader::scale(lerpv3(vec3(1.0, 1.0, 1.0), vec3(1.0, 2.0, 0.3), flatten));
	Shader::translate(vec3(0.0, 0.0, 28.0));
	Shader::scale(0.7);
	Shader::rotateY(10.0 * sinf(piPhase * 2.0));
	Shader::push();
	Resource::goraniTorso.draw();

	Shader::translate(vec3(16.0, bodyWidth, -4.0));
	Shader::rotateY(-20.0 * sFac);
	Shader::push();
	Resource::goraniLegBackTop.draw();

	Shader::translate(vec3(4.0, 0.0, -12.0));
	Shader::rotateY(-10.0 * sFac);
	Shader::push();
	Resource::goraniLegBackBottom.draw();

	Shader::pop();
	Shader::pop();

	Shader::translate(vec3(16.0, -bodyWidth, -4.0));
	Shader::rotateY(-20.0 * sFac);
	Shader::push();
	Resource::goraniLegBackTop.draw();

	Shader::translate(vec3(4.0, 0.0, -12.0));
	Shader::rotateY(-10.0 * sFac);
	Shader::push();
	Resource::goraniLegBackBottom.draw();

	Shader::pop();
	Shader::pop();

	Shader::translate(vec3(-16.0, bodyWidth, -4.0));
	Shader::rotateY(70.0 * sFac);
	Shader::push();
	Resource::goraniLegFrontTop.draw();

	Shader::translate(vec3(0.0, 0.0, -12.0));
	Shader::rotateY(-90.0 * sFac);
	Shader::push();
	Resource::goraniLegFrontBottom.draw();

	Shader::pop();
	Shader::pop();

	Shader::translate(vec3(-16.0, -bodyWidth, -4.0));
	Shader::rotateY(70.0 * sFac);
	Shader::push();
	Resource::goraniLegFrontTop.draw();

	Shader::translate(vec3(0.0, 0.0, -12.0));
	Shader::rotateY(-90.0 * sFac);
	Shader::push();
	Resource::goraniLegFrontBottom.draw();

	Shader::pop();
	Shader::pop();

	Shader::translate(vec3(-16.0, 0.0, 16.0));
	Shader::push();
	Resource::goraniNeck.draw();

	Shader::translate(vec3(0.0, 0.0, 12.0));
	Shader::push();
	Resource::goraniHead.draw();

	Shader::pop();
	Shader::pop();

	Object::draw();
	Shader::pop();
}

void Player::update() {
	Object::update();

	xx = flerp(xx, pos.x, 0.3);
	yy = flerp(yy, pos.y, 0.3);
	adir = flerp(adir, dir, 0.3);
	View::setViewDir(adir);

	if (aniPhase < 1.0) {
		aniPhase += 0.08;
	}
	else {
		aniPhase = 1.0;
	}

	if (dead == D_SUFFOCATE) {
		flatten = flerp(flatten, 1.0, 0.4);
	}

	if (dead != D_ALIVE) {
		if (Key::keyCheckPressed('r'))
			expire();
	}
	else {
		float dx = 0.0;
		float dy = 0.0;

		if (Key::keyCheckPressed('a')) {
			dir += 90.0;
		}

		if (Key::keyCheckPressed('d')) {
			dir += -90.0;
		}

		if (Key::keyCheckPressed('w')) {
			dx = Game::getGrid() * cosf(degToRad(dir));
			dy = Game::getGrid() * sinf(degToRad(dir));
			aniPhase = 0.0;
		}

		bool reject = false;

		pos.x += dx;
		pos.y += dy;
		cbUpdate();

		if (pos.y < ylimit) {
			reject = true;
		}

		if (!(srnd->collide(this, OBJ_WATER))) {
			float ddx = roundf(pos.x / Game::getGrid()) * Game::getGrid() - pos.x;
			
			if (pos.x + ddx > xlimit || pos.x + ddx < -xlimit) {
				reject = true;
			}
			else {
				dx += ddx;
				pos.x += ddx;
			}
		}

		if (srnd->collide(this, OBJ_RIGID)) {
			reject = true;
		}

		if (reject) {
			pos.x -= dx;
			pos.y -= dy;
			cbUpdate();
		}

		if (srnd->collide(this, OBJ_ENEMY)) {
			dead = D_SUFFOCATE;
		}

		Object* owater = srnd->collide(this, OBJ_WATER);
		Object* olog = srnd->collide(this, OBJ_LOG);

		if (owater) {
			if (olog) {
				float lx = olog->getPos().x;
				float side = roundf((pos.x - lx) / Game::getGrid());
				side = side > 1.0 ? 1.0 : side;
				side = side < -1.0 ? -1.0 : side;
				pos.x = lx + side * Game::getGrid();

				if (pos.x > xlimit + 0.5 * Game::getGrid() 
					|| pos.x < -xlimit - 0.5 * Game::getGrid())
					dead = D_OUTSIDE;

				pos += olog->getVel();
			}
			else {
				dead = D_DROWN;
				acc = vec3(0.0, 0.0, -0.5);
			}
		}

		ylimit = ylimit < pos.y - Game::getGrid() * 3.0 ? pos.y - Game::getGrid() * 3.0 : ylimit;
		View::setViewAt(pos.x, pos.y);
	}
}

Object& Player::locate(vec3 pos) {
	xx = pos.x;
	yy = pos.y;
	return Object::locate(pos);
}