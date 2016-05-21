//
// BetterCarryingEachOther 2016.03.17
// automatic enemy generation
//

#pragma once

#include "object.h"

class Generator : public Object {
public:
	enum type { TYPE_NONE, TYPE_ENEMY, TYPE_LOG };
private:
	enum type t;
	bool left;
	float spd;
	float gapMin, gapMax;
	float alarm;
	Object* create();
public:
	Generator(enum type t, float x, bool upper, float spd, float intvMin, float intvMax);
	void alarmSet();
	void update();
};

class MetaGenerator : public Object {
private:
	static float difRate;
	float target;
	float difficulty;
	void placeRoads();
	void placeRivers();
	void placeSafezone();
public:
	MetaGenerator();
	void update();
	void placeTrees(float y);
};