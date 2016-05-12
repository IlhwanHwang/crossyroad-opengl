//
// BetterCarryingEachOther 2016.03.15
// decoration objects
//

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

#include "utility.h"
#include "deco.h"
#include "view.h"
#include "game.h"
#include "resource.h"
#include "shader.h"

float Road::laneHeight = Game::getGrid();
float Road::laneLineWidth = 40.0;
float Road::laneLineSeperate = 60.0;
float Road::laneLineHeight = 3.0;

float Road::getLaneHeight() {
	return laneHeight;
}

Road::Road(int lane) : Object::Object(0.0, 0.0, 0.0, 0.0) {
	this->lane = lane;
	offset = -frand() * (laneLineWidth + laneLineSeperate);
	name = "Road";
}

void Road::draw() const {
	Resource::Tex::white.bind();
	Shader::push();
		Shader::translate(pos);

		for (float i = 0.0; i < (float)(lane * 2); i += 1.0) {
		Shader::push();
			Shader::translate(vec3(0.0, i * Game::getGrid(), 0.0));
			Shader::apply();
			Resource::roadLane.draw();
		Shader::pop();
		}

		for (float i = 0.5; i < (float)(lane - 1); i += 1.0) {
		Shader::push();
			Shader::translate(vec3(0.0, i * Game::getGrid(), 0.0));
			Shader::apply();
			Resource::roadLineWhite.draw();
		Shader::pop();

		Shader::push();
			Shader::translate(vec3(0.0,(i + (float)lane) * Game::getGrid(), 0.0));
			Shader::apply();
			Resource::roadLineWhite.draw();
		Shader::pop();
		}

		Shader::push();
			Shader::translate(vec3(0.0, ((float)lane - 0.5) * Game::getGrid(), 0.0));
			Shader::apply();
			Resource::roadLineYellow.draw();
		Shader::pop();

		Object::draw();
	Shader::pop();
}

void Road::update() {
	Object::update();
	if (View::getY() > pos.y + View::getZfar()) {
		expire();
	}
}

Env::Env(float x, float y, float cbWidth, float cbHeight, float cbOffX, float cbOffY)
	: Object::Object(cbWidth, cbHeight, cbOffX, cbOffY) {
	locate(vec3(x, y, 0.0));
}

Env::Env(vec3 pos) : Object::Object(0.0, 0.0, 0.0, 0.0) {
	locate(pos);
}

Grass::Grass(float y) : Env::Env(vec3(0.0, y, 0.0)) { name = "Grass"; }

void Grass::draw() const {
	Resource::Tex::white.bind();
	Shader::push();
	Shader::translate(pos);
	Shader::apply();
	Resource::grass.draw();

	Object::draw();
	Shader::pop();
}

Tree::Tree(float x, float y) : Env::Env(x, y, Game::getGrid(), Game::getGrid(), Game::getGrid() * 0.5, Game::getGrid() * 0.5) {
	radius = frandRange(20.0, 30.0);
	cat = OBJ_RIGID;
	name = "Tree";
}

void Tree::draw() const {
	Resource::Tex::tree.bind();
	Shader::push();
	Shader::translate(pos);
	Shader::apply();
	Resource::tree.draw();

	Object::draw();
	Shader::pop();
}

Deco::Deco(vec3 pos, Model* model, Texture* texture) {
	locate(pos);
	this->model = model;
	this->texture = texture;
	name = "Deco";
}

Deco::Deco(vec3 pos, vec3 orient, Model* model, Texture* texture)
	: Deco(pos, model, texture) {
	this->orient = orient;
}

void Deco::draw() const {
	Shader::push();
	Shader::translate(pos);
	Shader::rotateX(orient.x);
	Shader::rotateY(orient.y);
	Shader::rotateZ(orient.z);
	Shader::apply();
	texture->bind();
	model->draw();
	Object::draw();
	Shader::pop();
}