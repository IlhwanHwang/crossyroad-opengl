//
// BetterCarryingEachOther 2016.03.17
// viewing area management
//

#pragma once

#include "object.h"

class View {
public:
	enum mode {VIEW_FRONT, VIEW_BACK, VIEW_BIRD};

private:
	static float x;
	static float y;
	static float width;
	static float height;
	static float offsetTop;
	static float offsetLeft;
	static float tx;
	static float ty;
	static float zfar;
	static float znear;
	static float aspect;
	static float dist;
	static float viewDir;
	static mode viewMode;

public:
	static void init();
	static void setViewAt(float _x, float _y);
	static void setAspect(float asp);
	static void setViewDir(float dir);
	static void update();
	static void draw();
	static float getWidth();
	static float getHeight();
	static float getX();
	static float getY();
	static float getZfar();
	static float getZnear();
	static float getViewDir();
	static mode getViewMode();
};