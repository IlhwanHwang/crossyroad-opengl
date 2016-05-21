//
// BetterCarryingEachOther 2016.04.01
// resource management
//

#include "resource.h"
#include "vec.h"
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
Texture Resource::Tex::water;
Texture Resource::Tex::streetlight;
Texture Resource::Tex::noise;
Texture Resource::Tex::chicken;

Texture Resource::Norm::flat;
Texture Resource::Norm::grass;
Texture Resource::Norm::logstab;
Texture Resource::Norm::tree;
Texture Resource::Norm::road;
Texture Resource::Norm::water;
Texture Resource::Norm::tunnel;
Texture Resource::Norm::chicken;
Texture Resource::Norm::car;

Model Resource::temp;

Model Resource::grass[3];
Model Resource::grass9;
Model Resource::water;
Model Resource::logstab;
Model Resource::flower;
Model Resource::hill;
Model Resource::streetlight;

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

Model Resource::chicken;

void Resource::Tex::init() {
	test.load("test.png", GL_TEXTURE0);
	white.load("white.png", GL_TEXTURE0);
	carWhite.load("car.png", GL_TEXTURE0);
	carGray.load("car_gray.png", GL_TEXTURE0);
	carBlue.load("car_blue.png", GL_TEXTURE0);
	goraniWhole.load("gorani_whole.png", GL_TEXTURE0);
	wheel.load("wheel.png", GL_TEXTURE0);
	logstab.load("log.png", GL_TEXTURE0);
	tree.load("tree.png", GL_TEXTURE0);
	tunnel.load("tunnel.png", GL_TEXTURE0);
	road.load("road.png", GL_TEXTURE0);
	grass.load("grass.png", GL_TEXTURE0);
	water.load("water.png", GL_TEXTURE0);
	streetlight.load("streetlight.png", GL_TEXTURE0);
	noise.load("noise.png", GL_TEXTURE0);
	chicken.load("chicken.png", GL_TEXTURE0);
}

void Resource::Norm::init() {
	flat.load("normal_flat.png", GL_TEXTURE1);
	grass.load("normal_grass.png", GL_TEXTURE1);
	logstab.load("normal_log.png", GL_TEXTURE1);
	tree.load("normal_tree.png", GL_TEXTURE1);
	road.load("normal_road.png", GL_TEXTURE1);
	water.load("normal_water.png", GL_TEXTURE1);
	tunnel.load("normal_tunnel.png", GL_TEXTURE1);
	chicken.load("normal_chicken.png", GL_TEXTURE1);
	car.load("normal_car.png", GL_TEXTURE1);
}

void Resource::init() {
	Tex::init();
	Norm::init();

	const float wlimit = Game::getWidthLimit();
	const float xlimit = Game::getGrid() * 3.5;
	const float grid = Game::getGrid();
	const float thickness = 3.0;

	grass[0].load("grass1.obj");
	grass[1].load("grass2.obj");
	grass[2].load("grass3.obj");
	grass9.load("grass9.obj");
	water.load("water.obj");
	logstab.load("log.obj");
	flower.load("flower.obj");
	hill.load("hill.obj");
	streetlight.load("streetlight.obj");

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

	chicken.load("chicken.obj");
}