//
// BetterCarryingEachOther 2016.05.16
// control module
//

#pragma once

#include "vec.h"

class Control {
private:
	static bool day;
	static bool ssao;

public:
	static bool isDay() { return day; }
	static bool isSSAO() { return ssao; }
	static vec4 getAmbient() { return day ? vec4(0.5, 0.75, 1.0, 0.5) : vec4(0.5, 1.0, 1.0, 0.2); }
	static vec4 getFog() { return day ? vec4(0.8, 0.9, 1.0, 1.0) : vec4(0.0, 0.1, 0.2, 1.0); }

	static void update();
};