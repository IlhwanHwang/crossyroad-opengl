//
// BetterCarryingEachOther 2016.04.01
// resource management
//

#include "vec.h"
#include "resource.h"
#include "game.h"
#include "lodepng.h"

Texture Resource::Tex::test;
Texture Resource::Tex::white;
Texture Resource::Tex::carWhite;
Texture Resource::Tex::carGray;
Texture Resource::Tex::carBlue;
Texture Resource::Tex::goraniWhole;
Texture Resource::Tex::wheel;
Texture Resource::Tex::busRed;
Texture Resource::Tex::busYellow;
Texture Resource::Tex::busBlue;
Texture Resource::Tex::logstab;
Texture Resource::Tex::tree;
Texture Resource::Tex::tunnel;

Model Resource::canonical;

Model Resource::temp;

Model Resource::grass;
Model Resource::water;
Model Resource::logstab;
Model Resource::flower;
Model Resource::hill;

Model Resource::player;

Model Resource::car;
Model Resource::bus;
Model Resource::wheel;
Model Resource::tree;
Model Resource::tunnel;
Model Resource::drain;

Model Resource::goraniTorso;
Model Resource::goraniHead;
Model Resource::goraniNeck;
Model Resource::goraniLegFrontTop;
Model Resource::goraniLegFrontBottom;
Model Resource::goraniLegBackTop;
Model Resource::goraniLegBackBottom;

Model Resource::roadLane;
Model Resource::roadLineYellow;
Model Resource::roadLineWhite;

void Resource::Tex::init() {
	test.load("test.png");
	white.load("white.png");
	carWhite.load("car.png");
	carGray.load("car_gray.png");
	carBlue.load("car_blue.png");
	goraniWhole.load("gorani_whole.png");
	wheel.load("wheel.png");
	busRed.load("bus_red.png");
	busYellow.load("bus_yellow.png");
	busBlue.load("bus_blue.png");
	logstab.load("log.png");
	tree.load("tree.png");
	tunnel.load("tunnel.png");
	glActiveTexture(GL_TEXTURE0);
}

void Resource::init() {
	Tex::init();

	/*
	canonical.addPoint(vec3(-1.0, -1.0, 0.0), vec2(0.0, 0.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.addPoint(vec3(-1.0, 1.0, 0.0), vec2(0.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.addPoint(vec3(1.0, -1.0, 0.0), vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.addPoint(vec3(-1.0, 1.0, 0.0), vec2(0.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.addPoint(vec3(1.0, -1.0, 0.0), vec2(1.0, 0.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.addPoint(vec3(1.0, 1.0, 0.0), vec2(1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 1.0));
	canonical.generate();
	*/

	const float wlimit = Game::getWidthLimit();
	const float xlimit = Game::getGrid() * 3.5;
	const float grid = Game::getGrid();
	const float thickness = 3.0;

	/*
	temp.addBox(vec3(-30.0, -30.0, 0.0), vec3(0.0, 30.0, 30.0), Color::white);
	temp.addBox(vec3(0.0, -30.0, 0.0), vec3(30.0, 30.0, 30.0), Color::black);
	temp.addBox(vec3(-30.0, -30.0, 30.0), vec3(0.0, 30.0, 60.0), Color::black);
	temp.addBox(vec3(0.0, -30.0, 30.0), vec3(30.0, 30.0, 60.0), Color::white);
	temp.generate();
	*/

	/*
	grass.addBox(vec3(-xlimit, -grid / 2.0, -grid), vec3(xlimit, grid / 2.0, thickness), Color::grass);
	grass.addBox(vec3(-wlimit, -grid / 2.0, -grid), vec3(-xlimit, grid / 2.0, 2.0*thickness), Color::darkgrass);
	grass.addBox(vec3(xlimit, -grid / 2.0, -grid), vec3(wlimit, grid / 2.0, 2.0*thickness), Color::darkgrass);
	grass.generate();
	*/

	//roadLane.addBox(vec3(-wlimit, -grid / 2.0, -grid), vec3(wlimit, grid / 2.0, 0.0), Color::gray);
	//roadLane.generate();

	//roadLineYellow.addBox(vec3(-wlimit, -3.0, 0.0), vec3(wlimit, 3.0, thickness), Color::yellow);
	//roadLineYellow.generate();

	const float w = 40.0;
	const float wsep = 60.0;
	for (float dx = wsep / 2.0; dx < wlimit; dx += w + wsep) {
		//roadLineWhite.addBox(
		//	vec3(dx, -3.0, 0.0), vec3(dx + w, 3.0, thickness), Color::white);
		//roadLineWhite.addBox(
		//	vec3(-dx - w, -3.0, 0.0), vec3(-dx, 3.0, thickness), Color::white);
	}
	//roadLineWhite.generate();

	water.load("water.obj");
	water.generate();

	logstab.load("log.obj");
	logstab.generate();

	flower.load("flower.obj");
	flower.generate();

	hill.load("hill.obj");
	hill.generate();

	player.load("player.obj");
	player.generate();

	car.load("car.obj");
	car.generate();

	bus.load("bus.obj");
	bus.generate();

	wheel.load("wheel.obj");
	wheel.generate();

	tree.load("tree.obj");
	tree.generate();

	tunnel.load("tunnel.obj");
	tunnel.generate();

	drain.load("drain.obj");
	drain.generate();

	goraniTorso.load("gorani.obj", "torso");
	goraniHead.load("gorani.obj", "head");
	goraniNeck.load("gorani.obj", "neck");
	goraniLegFrontTop.load("gorani.obj", "leg_front_top");
	goraniLegFrontBottom.load("gorani.obj", "leg_front_bottom");
	goraniLegBackTop.load("gorani.obj", "leg_back_top");
	goraniLegBackBottom.load("gorani.obj", "leg_back_bottom");

	goraniTorso.generate();
	goraniHead.generate();
	goraniNeck.generate();
	goraniLegFrontTop.generate();
	goraniLegFrontBottom.generate();
	goraniLegBackTop.generate();
	goraniLegBackBottom.generate();
}