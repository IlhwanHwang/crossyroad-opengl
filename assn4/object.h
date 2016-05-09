//
// BetterCarryingEachOther 2016.03.11
// abstract object class
//

#pragma once

#include <list>
#include "model.h"

using namespace std;

class Object {
protected:
	static int count;

	const char* name;

	enum Category { OBJ_ANY, OBJ_NONE, OBJ_RIGID, OBJ_ENEMY, OBJ_WATER, OBJ_LOG };
	enum Category cat;
	float cbWidth, cbHeight, cbOffX, cbOffY;
	vec3 pos, vel, acc;

	bool expired;

	class CBox {
	private:
		float x1, y1, x2, y2;

	public:
		bool check(CBox *other);
		bool inclusion(float x, float y);
		void locate(float x, float y, float w, float h, float ofx, float ofy);
	};

	CBox cb;
	void cbUpdate();

	Model *mod;
	list<Object*> children;

public:
	static void countReset();
	static int countGet();

	Object(float cbWidth, float cbHeight, float cbOffX, float cbOffY);
	Object();
	~Object();

	virtual void echo();

	virtual void draw() const;
	virtual void update();
	virtual void push(Object* o);
	virtual void expire();
	virtual Object* collide(Object* other, enum Category cat);

	virtual Object& locate(vec3 pos);

	virtual Object& move(vec3 dpos);
	virtual Object& exert(vec3 dvel);

	virtual Object& setX(float x);
	virtual Object& setY(float y);
	virtual Object& setZ(float z);
	virtual Object& setXvel(float xspd);
	virtual Object& setYvel(float yspd);
	virtual Object& setZvel(float zspd);
	virtual Object& setXacc(float xacc);
	virtual Object& setYacc(float yacc);
	virtual Object& setZacc(float zacc);

	virtual vec3 getPos();
	virtual vec3 getVel();
	virtual vec3 getAcc();
	virtual bool isExpired();
	virtual enum Category getCat();
};