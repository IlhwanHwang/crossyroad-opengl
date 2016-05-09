//
// BetterCarryingEachOther 2016.04.01
// resource management
//

#pragma once

#include <GL/glut.h>
#include "vec.h"
#include "model.h"
#include "texture.h"

class Resource {
public:
	class Tex {
	public:
		static Texture test;
		static Texture white;
		static Texture carWhite;
		static Texture carGray;
		static Texture carBlue;
		static Texture goraniWhole;
		static Texture wheel;
		static Texture busRed;
		static Texture busYellow;
		static Texture busBlue;
		static Texture logstab;
		static Texture tree;
		static Texture tunnel;

		static void init();
	};

	static Model canonical;

	static Model temp;

	static Model grass;
	static Model water;
	static Model logstab;
	static Model flower;
	static Model hill;

	static Model player;

	static Model car;
	static Model bus;
	static Model wheel;
	static Model tree;
	static Model tunnel;
	static Model drain;

	static Model goraniTorso;
	static Model goraniHead;
	static Model goraniNeck;
	static Model goraniLegFrontTop;
	static Model goraniLegFrontBottom;
	static Model goraniLegBackTop;
	static Model goraniLegBackBottom;

	static Model roadLane;
	static Model roadLineYellow;
	static Model roadLineWhite;

	static void init();
};