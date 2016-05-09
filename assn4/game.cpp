//
// BetterCarryingEachOther 2016.03.11
// game manage module
//

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cstdlib>
#include <ctime>

#include "game.h"
#include "player.h"
#include "enemy.h"
#include "deco.h"
#include "view.h"
#include "generator.h"
#include "shader.h"
#include "resource.h"
#include "null.h"


using namespace std;

Object* Game::pool = nullptr;
Player* Game::player = nullptr;
Deco* Game::hillL = nullptr;
Deco* Game::hillR = nullptr;
float Game::grid = 64.0;
float Game::widthLimit = Game::grid * 6.0;
int Game::frameInterval = 16;
Framebuffer Game::fb((int)View::getWidth(), (int)View::getHeight());

GLuint can;

void Game::init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	srand(time(NULL));
	setup();

	fb.generate();
}

void Game::setup() {
	MetaGenerator *mg = new MetaGenerator();

	for (float y = -grid * 4.0; y < grid * 4.0; y += grid)
		mg->placeFlowers(y);
	for (float y = -grid * 4.5; y < 0.0; y += grid)
		mg->placeTrees(y);

	pool = new Object();
	hillL = new Deco(vec3(0.0, 0.0, 0.0), &Resource::hill, &Resource::Tex::white);
	hillR = new Deco(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 180.0), &Resource::hill, &Resource::Tex::white);
	pool->push(mg);
	pool->push(hillL);
	pool->push(hillR);

	NullLimiter* nl = new NullLimiter(0.0);
	Deco* hillB = new Deco(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 90.0), &Resource::hill, &Resource::Tex::white);
	nl->push(hillB);
	pool->push(nl);

	player = new Player(pool);
}

void Game::clear() {
	delete player;
	pool->expire();
	delete pool;
}

void Game::reshape(int w, int h) {
	View::setAspect((float)w / h);
	glViewport(0, 0, w, h);
}

void Game::draw() {
	fb.bind();

	Shader::useWire();
	glClearDepth(1.0);
	glClearColor(0.5, 0.75, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	pool->draw();
	player->draw();
	
	fb.unbind();

	Shader::useFramePass();
	glClearDepth(1.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	fb.bindDiffuse();
	Model::drawFramePassCanonical();

	Shader::useWire();

	glutSwapBuffers();
}

void Game::update() {
	Object::countReset();

	if (player->isExpired()) {
		View::init();
		clear();
		setup();
	}
	hillL->locate(vec3(0.0, player->getPos().y, 0.0));
	hillR->locate(vec3(0.0, player->getPos().y, 0.0));
	pool->update();
	player->update();
	View::update();

	cout << Object::countGet() << " Objects in scope" << endl;
}

float Game::getGrid() {
	return grid;
}

float Game::getWidthLimit() {
	return widthLimit;
}

int Game::getFrameInterval() {
	return frameInterval;
}