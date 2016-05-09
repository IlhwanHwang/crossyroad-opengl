//
// BetterCarryingEachOther 2016.03.12
// enemy class
//

#pragma once

#include "object.h"
#include "texture.h"

class Enemy : public Object {
protected:
	float dist;
public:
	Enemy(float cbWidth, float cbHeight, float cbOffX, float cbOffY);
	void update();
};

class Bus : public Enemy {
private:
	Texture* tex;
public:
	Bus();
	void draw() const;
};

class Car : public Enemy {
private:
	Texture* tex;
public:
	Car();
	void draw() const;
};