//
// BetterCarryingEachOther 2016.03.11
// player class
//

#pragma once

#include "object.h"

class Player : public Object {
private:
	enum deadState { D_ALIVE, D_DROWN, D_SUFFOCATE, D_OUTSIDE };
	enum deadState dead;

	static float xlimit;
	float xx, yy;
	float ylimit;
	float dir, adir;
	float flatten;
	float aniPhase;

	Object* srnd;
public:
	static float getXlimit();
	Player(Object* srnd);
	void draw() const;
	void update();
	Object& locate(vec3 pos);
};