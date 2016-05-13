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
Texture Resource::Tex::logstab;
Texture Resource::Tex::tree;
Texture Resource::Tex::tunnel;
Texture Resource::Tex::road;
Texture Resource::Tex::grass;

Model Resource::temp;

Model Resource::grass;
Model Resource::water;
Model Resource::logstab;
Model Resource::flower;
Model Resource::hill;

Model Resource::player;

Model Resource::car;
Model Resource::wheel;
Model Resource::tree;
Model Resource::tunnel;
Model Resource::drain;
Model Resource::road[4];

Model Resource::goraniTorso;
Model Resource::goraniHead;
Model Resource::goraniNeck;
Model Resource::goraniLegFrontTop;
Model Resource::goraniLegFrontBottom;
Model Resource::goraniLegBackTop;
Model Resource::goraniLegBackBottom;

void Resource::Tex::init() {
	test.load("test.png");
	white.load("white.png");
	carWhite.load("car.png");
	carGray.load("car_gray.png");
	carBlue.load("car_blue.png");
	goraniWhole.load("gorani_whole.png");
	wheel.load("wheel.png");
	logstab.load("log.png");
	tree.load("tree.png");
	tunnel.load("tunnel.png");
	road.load("road.png");
	grass.load("grass.png");
	glActiveTexture(GL_TEXTURE0);
}

void Resource::init() {
	Tex::init();

	const float wlimit = Game::getWidthLimit();
	const float xlimit = Game::getGrid() * 3.5;
	const float grid = Game::getGrid();
	const float thickness = 3.0;

	
	temp.addBox(vec3(-30.0, -30.0, 0.0), vec3(0.0, 30.0, 30.0));
	temp.addBox(vec3(0.0, -30.0, 0.0), vec3(30.0, 30.0, 30.0));
	temp.addBox(vec3(-30.0, -30.0, 30.0), vec3(0.0, 30.0, 60.0));
	temp.addBox(vec3(0.0, -30.0, 30.0), vec3(30.0, 30.0, 60.0));
	temp.generate();

	grass.addBox(vec3(-xlimit, -grid / 2.0, -grid), vec3(xlimit, grid / 2.0, thickness));
	grass.addBox(vec3(-wlimit, -grid / 2.0, -grid), vec3(-xlimit, grid / 2.0, 2.0*thickness));
	grass.addBox(vec3(xlimit, -grid / 2.0, -grid), vec3(wlimit, grid / 2.0, 2.0*thickness));
	grass.generate();

	water.load("water.obj");
	logstab.load("log.obj");
	flower.load("flower.obj");
	hill.load("hill.obj");
	grass.load("grass.obj");

	player.load("player.obj");
	car.load("car.obj");
	wheel.load("wheel.obj");
	tree.load("tree.obj");
	tunnel.load("tunnel.obj");
	drain.load("drain.obj");

	road[0].load("road1.obj");
	road[1].load("road2.obj");
	road[2].load("road3.obj");
	road[3].load("road4.obj");

	goraniTorso.load("gorani.obj", "torso");
	goraniHead.load("gorani.obj", "head");
	goraniNeck.load("gorani.obj", "neck");
	goraniLegFrontTop.load("gorani.obj", "leg_front_top");
	goraniLegFrontBottom.load("gorani.obj", "leg_front_bottom");
	goraniLegBackTop.load("gorani.obj", "leg_back_top");
	goraniLegBackBottom.load("gorani.obj", "leg_back_bottom");
}