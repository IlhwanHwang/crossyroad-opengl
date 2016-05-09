//
// BetterCarryingEachOther 2016.03.15
// decoration objects
//
#pragma once

#include "object.h"
#include "texture.h"
#include "model.h"

class Road : public Object {
private:
	static float laneHeight;
	static float laneLineWidth;
	static float laneLineHeight;
	static float laneLineSeperate;

	int lane;
	float offset;
public:
	static float getLaneHeight();

	Road(int lane);
	void draw() const;
	void update();
};

class Env : public Object {
public:
	Env(float x, float y, float cbWidth, float cbHeight, float cbOffX, float cbOffY);
	Env(vec3 pos);
};

class Grass : public Env {
public:
	Grass(float y);
	void draw() const;
};

class Tree : public Env {
private:
	float radius;
public:
	Tree(float x, float y);
	void draw() const;
};

class Deco : public Object {
private:
	Model* model;
	Texture* texture;
	vec3 orient;
public:
	Deco(vec3 pos, Model* model, Texture* texture);
	Deco(vec3 pos, vec3 orient, Model* model, Texture* texture);
	void draw() const;
};