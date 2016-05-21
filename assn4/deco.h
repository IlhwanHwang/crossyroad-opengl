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
	int lane;
public:
	Road(int lane);
	void draw() const;
	void update();
};

class Env : public Object {
public:
	Env(float x, float y, float cbWidth, float cbHeight, float cbOffX, float cbOffY);
	Env(vec3 pos);
};

class Tree : public Env {
private:
	float scale, rotation;

public:
	Tree(float x, float y);
	void draw() const;
};

class Deco : public Object {
private:
	Model* model;
	Texture* texture;
	Texture* normalmap;
	vec3 orient;
	vec2 uvshift;
public:
	Deco(vec3 pos, Model* model, Texture* texture, Texture* normalmap);
	Deco(vec3 pos, vec3 orient, Model* model, Texture* texture, Texture* normalmap);
	void draw() const;
	void shift(vec2 uv) { uvshift = uv; }
};