//
// BetterCarryingEachOther 2016.04.01
// resource management
//

#pragma once

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
		static Texture logstab;
		static Texture tree;
		static Texture tunnel;
		static Texture road;
		static Texture grass;
		static Texture water;
		static Texture streetlight;
		static Texture noise;
		static Texture chicken;

		static void init();
	};

	class Norm {
	public:
		static Texture flat;
		static Texture grass;
		static Texture logstab;
		static Texture tree;
		static Texture road;
		static Texture water;
		static Texture tunnel;
		static Texture chicken;
		static Texture car;

		static void init();
	};

	static Model temp;

	static Model grass[3];
	static Model grass9;
	static Model water;
	static Model logstab;
	static Model flower;
	static Model hill;
	static Model streetlight;

	static Model player;

	static Model car;
	static Model wheel;
	static Model tree;
	static Model tunnel;
	static Model drain;
	static Model road[4];

	static Model goraniTorso;
	static Model goraniHead;
	static Model goraniNeck;
	static Model goraniLegFrontTop;
	static Model goraniLegFrontBottom;
	static Model goraniLegBackTop;
	static Model goraniLegBackBottom;

	static Model chicken;

	static void init();
};