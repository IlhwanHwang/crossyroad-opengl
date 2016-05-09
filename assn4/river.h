//
// BetterCarryingEachOther 2016.04.03
// objects related to river
//

#pragma once

#include "deco.h"

class Water : public Env {
private:
	float phase;
public:
	Water(float y);
	void draw() const;
	void update();
};

class Log : public Object {
public:
	Log();
	void draw() const;
	void update();
};