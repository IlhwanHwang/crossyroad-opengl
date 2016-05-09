//
// BetterCarryingEachOther 2016.03.11
// game manage module
//

#pragma once

#include <GL/glew.h>
#include "player.h"
#include "deco.h"
#include "framebuffer.h"

class Game {
private:
	static Object* pool;
	static Player* player;
	static Deco* hillL;
	static Deco* hillR;
	static float grid;
	static float widthLimit;
	static int frameInterval;
	static Framebuffer fb;

public:
	static void init();
	static void setup();
	static void clear();
	static void draw();
	static void update();
	static void reshape(int w, int h);

	static float getGrid();
	static float getWidthLimit();
	static int getFrameInterval();
};