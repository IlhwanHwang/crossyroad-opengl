//
// BetterCarryingEachOther 2016.04.03
// objects related to river
//

#pragma once

#include "game.h"
#include "shader.h"
#include "river.h"
#include "utility.h"
#include "resource.h"

Water::Water(float y)
	: Env::Env(0.0, y,
		Game::getWidthLimit() * 2.0, Game::getGrid(),
		Game::getWidthLimit(), Game::getGrid() / 2.0) {
	phase = 0.0;
	cat = OBJ_WATER;
	name = "Water";
}

void Water::draw() const {
	Resource::Tex::water.bind();
	Resource::Norm::water.bind();

	Shader::push();
		Shader::translate(pos);
		Shader::translate(vec3(0.0, 0.0, -4.0));
	
		for (float dx = -Game::getWidthLimit() - phase; dx < Game::getWidthLimit(); dx += Game::getGrid() * 2.0) {
		Shader::push();
			Shader::translate(vec3(dx, 0.0, 0.0));
			Shader::shift(vec2(dx / 64.0 / 4.0, -pos.y / 64.0 / 4.0));
			Shader::apply();
			Resource::water.draw();
		Shader::pop();
		}

		Object::draw();
	Shader::pop();
}

void Water::update() {
	phase += 0.2;
	if (phase > Game::getGrid() * 2.0)
		phase -= Game::getGrid() * 2.0;

	Object::update();
}

Log::Log()
	: Object::Object(
		Game::getGrid() * 2.5, Game::getGrid(), 
		Game::getGrid() * 1.25, Game::getGrid() * 0.5) {
	cat = OBJ_LOG;
	name = "Log";
}

void Log::draw() const {
	Shader::push();
		Shader::translate(pos);
		Shader::scale(0.8);
		Shader::apply();

		Resource::Norm::logstab.bind();
		Resource::Tex::logstab.bind();
		Resource::logstab.draw();

		Object::draw();
	Shader::pop();
}

void Log::update() {
	Object::update();

	if (pos.x > Game::getWidthLimit() || pos.x < -Game::getWidthLimit())
		expire();
}