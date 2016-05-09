//
// BetterCarryingEachOther 2016.04.29
// null objects
//
#pragma once

#include "object.h"

class NullLimiter : public Object {
public:
	NullLimiter(float y);
	void update();
};