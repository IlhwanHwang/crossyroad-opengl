//
// BetterCarryingEachOther 2016.03.11
// abstract object class
//

#include <iostream>

#include "object.h"
#include "view.h"
#include "game.h"
#include "model.h"

int Object::count = 0;

void Object::countReset() {
	count = 0;
}

int Object::countGet() {
	return count;
}

Object::Object(float cbWidth, float cbHeight, float cbOffX, float cbOffY) {
	this->cbWidth = cbWidth;
	this->cbHeight = cbHeight;
	this->cbOffX = cbOffX;
	this->cbOffY = cbOffY;

	cat = OBJ_NONE;
	expired = false;

	name = "Undefined";
}

Object::Object() : Object::Object(0.0, 0.0, 0.0, 0.0) {
}

Object::~Object() {
}

bool Object::CBox::check(CBox *other) {
	return this->x1 <= other->x2 && this->x2 >= other->x1 &&
		this->y1 <= other->y2 && this->y2 >= other->y1;
}

bool Object::CBox::inclusion(float x, float y) {
	return x > x1 && x < x2 && y > y1 && y < y2;
}

void Object::CBox::locate(float x, float y, float w, float h, float ofx, float ofy) {
	x1 = x - ofx;
	y1 = y - ofy;
	x2 = x + w - ofx;
	y2 = y + h - ofy;
}

void Object::cbUpdate() {
	cb.locate(pos.x, pos.y, cbWidth, cbHeight, cbOffX, cbOffY);
}

void Object::echo() {
	cout << name << endl;
}

void Object::draw() const {
	for (list<Object*>::const_iterator itor = children.begin();
		itor != children.end(); ++itor) {
		(*itor)->draw();
	}
}

void Object::update() {
	count++;

	vel += acc;
	pos += vel;
	cbUpdate();

	for (list<Object*>::iterator itor = children.begin();
		itor != children.end(); ++itor) {
		(*itor)->update();
	}

	list<Object*>::iterator itor = children.begin();
	while (itor != children.end()) {
		list<Object*>::iterator citor = itor;
		++itor;

		Object* o = (*citor);
		if (o->isExpired()) {
			delete o;
			children.erase(citor);
		}
	}
}

void Object::push(Object* o) {
	children.push_back(o);
}

void Object::expire() {
	expired = true;

	list<Object*>::iterator itor = children.begin();
	while (itor != children.end()) {
		list<Object*>::iterator citor = itor;
		++itor;

		Object *o = (*citor);
		o->expire();
		delete o;
	}
}

Object* Object::collide(Object* other, enum Category cat) {
	if ((this->cat == cat || cat == OBJ_ANY) && (other->cb.check(&(this->cb))))
		return this;

	for (list<Object*>::iterator itor = children.begin();
		itor != children.end(); ++itor) {
		Object* collidee = (*itor)->collide(other, cat);
		if (collidee != nullptr)
			return collidee;
	}

	return nullptr;
}

//------//

Object& Object::locate(vec3 pos) {
	this->pos = pos;
	return (*this);
}

Object& Object::move(vec3 dpos) {
	pos += dpos;
	return (*this);
}

Object& Object::exert(vec3 dvel) {
	vel += dvel;
	return (*this);
}

Object& Object::setX(float x) {
	pos.x = x;
	return (*this);
}

Object& Object::setY(float y) {
	pos.y = y;
	return (*this);
}

Object& Object::setZ(float z) {
	pos.z = z;
	return (*this);
}

Object& Object::setXvel(float xspd) {
	vel.x = xspd;
	return (*this);
}

Object& Object::setYvel(float yspd) {
	vel.y = yspd;
	return (*this);
}

Object& Object::setZvel(float yspd) {
	vel.y = yspd;
	return (*this);
}

Object& Object::setXacc(float xacc) {
	acc.x += xacc;
	return (*this);
}

Object& Object::setYacc(float yacc) {
	acc.y += yacc;
	return (*this);
}

Object& Object::setZacc(float yacc) {
	acc.z += yacc;
	return (*this);
}

vec3 Object::getPos() {
	return pos;
}

vec3 Object::getVel() {
	return vel;
}

vec3 Object::getAcc() {
	return acc;
}

bool Object::isExpired() {
	return expired;
}

enum Object::Category Object::getCat() {
	return cat;
}