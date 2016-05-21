//
// BetterCarryingEachOther 2016.05.16
// light emitter class
//

#pragma once

#include "object.h"
#include "shader.h"

class Light : public Object {
private:
	vec4 color;
public:
	Light(vec3 pos, vec4 color);
	void update();
};

class StreetLight : public Object {
private:
	float angle;
	vec3 dpos;
public:
	StreetLight(vec3 pos);
	void draw() const;
};