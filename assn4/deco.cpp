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

#include "debug.h"

Road::Road(int lane) : Object::Object(0.0, 0.0, 0.0, 0.0) {
	this->lane = lane;
	name = "Road";
}

void Road::draw() const {
	Resource::Tex::road.bind();
	Shader::push();
		Shader::translate(pos);
		Shader::translate(vec3(0.0, (lane - 0.5) * Game::getGrid(), 0.0));
		Shader::apply();
		Resource::road[lane - 1].draw();
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
	Resource::Tex::grass.bind();
	Shader::push();
	Shader::translate(pos);
	Shader::apply();
	Shader::getPhysicalShader().setUVOffset(vec2(0.0, pos.y / Game::getGrid() / 3.0));
	Resource::grass.draw();
	Shader::getPhysicalShader().setUVOffset(vec2(0.0, 0.0));

	Object::draw();
	Shader::pop();
}

Tree::Tree(float x, float y) : Env::Env(x, y, Game::getGrid(), Game::getGrid(), Game::getGrid() * 0.5, Game::getGrid() * 0.5) {
	scale = frandRange(1.0, 1.5);
	rotation = frandRange(0.0, 360.0);
	cat = OBJ_RIGID;
	name = "Tree";
}

void Tree::draw() const {
	Resource::Tex::tree.bind();
	Shader::push();
	Shader::translate(pos);
	Shader::scale(vec3(scale, scale, scale));
	Shader::rotateZ(rotation);
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