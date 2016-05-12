//
// BetterCarryingEachOther 2016.03.12
// enemy class
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>

#include "object.h"
#include "enemy.h"
#include "view.h"
#include "deco.h"
#include "shader.h"
#include "resource.h"
#include "game.h"

Enemy::Enemy(float cbWidth, float cbHeight, float cbOffX, float cbOffY)
	: Object::Object(cbWidth, cbHeight, cbOffX, cbOffY) {
	cat = OBJ_ENEMY;
	dist = 0.0;
}

void Enemy::update() {
	Object::update();
	dist += length(vel);

	if (pos.x > Game::getWidthLimit() || pos.x < -Game::getWidthLimit())
		expire();
}

Bus::Bus() : Enemy::Enemy(80.0, 40.0, 40.0, 20.0) {
	switch (rand() % 3) {
	case 0: tex = &Resource::Tex::busRed; break;
	case 1: tex = &Resource::Tex::busYellow; break;
	case 2: tex = &Resource::Tex::busBlue; break;
	}

	name = "Bus";
}

void Bus::draw() const {
	tex->bind();

	const float wheelHeight = 8.0;

	Shader::push();
	Shader::translate(pos);
	Shader::translate(vec3(0.0, 0.0, wheelHeight + 3.0));
	if (vel.x > 0)
		Shader::rotateZ(180.0);
	Shader::apply();
	Resource::bus.draw();

	const float carWidth = 28.0;
	const float wheelFront = -28.0;
	const float wheelBack = 24.0;
	const float wheelAngle = dist / wheelHeight / DegreesToRadians;

	Resource::Tex::wheel.bind();

	Shader::push();
	Shader::translate(vec3(wheelFront, carWidth, 0.0));
	Shader::rotateX(90.0);
	Shader::rotateZ(wheelAngle);
	Shader::apply();
	Resource::wheel.draw();
	Shader::pop();

	Shader::push();
	Shader::translate(vec3(wheelFront, -carWidth, 0.0));
	Shader::rotateX(90.0);
	Shader::rotateZ(wheelAngle);
	Shader::apply();
	Resource::wheel.draw();
	Shader::pop();

	Shader::push();
	Shader::translate(vec3(wheelBack, carWidth, 0.0));
	Shader::rotateX(90.0);
	Shader::rotateZ(wheelAngle);
	Shader::apply();
	Resource::wheel.draw();
	Shader::pop();

	Shader::push();
	Shader::translate(vec3(wheelBack, -carWidth, 0.0));
	Shader::rotateX(90.0);
	Shader::rotateZ(wheelAngle);
	Shader::apply();
	Resource::wheel.draw();
	Shader::pop();

	Object::draw();
	Shader::pop();
}

Car::Car() : Enemy::Enemy(70.0, 30.0, 35.0, 15.0){
	switch (rand() % 4) {
	case 0: tex = &Resource::Tex::carWhite; break;
	case 1: tex = &Resource::Tex::carGray; break;
	case 2: tex = &Resource::Tex::carGray; break;
	case 3: tex = &Resource::Tex::carBlue; break;
	}
	name = "Car";
}

void Car::draw() const {
	tex->bind();

	Shader::push();
		Shader::translate(pos);
		Shader::translate(vec3(0.0, 0.0, 3.0));
		if (vel.x > 0)
			Shader::rotateZ(180.0);
		Shader::apply();
		Resource::car.draw();

		const float carWidth = 20.0;
		const float wheelFront = -30.0;
		const float wheelBack = 28.0;
		const float wheelHeight = 12.0;
		const float wheelAngle = dist / wheelHeight / DegreesToRadians;

		Resource::Tex::wheel.bind();

		Shader::push();
			Shader::translate(vec3(wheelFront, carWidth, wheelHeight));
			Shader::rotateX(90.0);
			Shader::rotateZ(wheelAngle);
			Shader::apply();
			Resource::wheel.draw();
		Shader::pop();

		Shader::push();
			Shader::translate(vec3(wheelFront, -carWidth, wheelHeight));
			Shader::rotateX(90.0);
			Shader::rotateZ(wheelAngle);
			Shader::apply();
			Resource::wheel.draw();
		Shader::pop();

		Shader::push();
			Shader::translate(vec3(wheelBack, carWidth, wheelHeight));
			Shader::rotateX(90.0);
			Shader::rotateZ(wheelAngle);
			Shader::apply();
			Resource::wheel.draw();
		Shader::pop();

		Shader::push();
			Shader::translate(vec3(wheelBack, -carWidth, wheelHeight));
			Shader::rotateX(90.0);
			Shader::rotateZ(wheelAngle);
			Shader::apply();
			Resource::wheel.draw();
		Shader::pop();

		Object::draw();
	Shader::pop();
}