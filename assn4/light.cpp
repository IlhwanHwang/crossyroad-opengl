//
// BetterCarryingEachOther 2016.05.16
// light emitter class
//

#include "light.h"
#include "resource.h"
#include "control.h"

Light::Light(vec3 pos, vec4 color) : color(color) {
	locate(pos);
}

void Light::update() {
	if (!Control::isDay()) {
		Shader::lightPush(vec4(pos, 1.0), color);
	}
}

StreetLight::StreetLight(vec3 pos) : Object() {
	switch (rand() % 4) {
	case 0:
		angle = 180.0;
		dpos = vec3(16.0, 0.0, 96.0);
		break;
	case 1:
		angle = 270.0;
		dpos = vec3(0.0, 16.0, 96.0);
		break;
	case 2:
		angle = 0.0;
		dpos = vec3(-16.0, 0.0, 96.0);
		break;
	case 3:
		angle = 90.0;
		dpos = vec3(0.0, -16.0, 96.0);
		break;
	}
	locate(pos);
	push(new Light(pos + dpos, vec4(1.0, 0.8, 0.6, 100.0)));
}

void StreetLight::draw() const {
	Shader::push();
		Shader::translate(pos);
		Shader::rotateZ(angle);
		Shader::apply();
		Resource::Tex::streetlight.bind();
		Resource::Norm::flat.bind();
		Resource::streetlight.draw();
		Object::draw();
	Shader::pop();
}