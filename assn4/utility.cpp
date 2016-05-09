//
// BetterCarryingEachOther 2016.03.15
// utility functions
//

#include "utility.h"
#include "vec.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

float frand() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float frandRange(float a, float b) {
	return frand() * (b - a) + a;
}

float flerp(float a, float b, float x) {
	return a * (1.0 - x) + b * x;
}

vec3 lerpv3(vec3 a, vec3 b, float x) {
	return vec3(flerp(a.x, b.x, x), flerp(a.y, b.y, x), flerp(a.z, b.z, x));
}

vector<string> tokenize(string str, string delim) {
	vector<string> v;
	size_t seek = 0;

	while (str.length() > seek) {
		size_t pos; 
		pos = str.find_first_of(delim, seek);

		if (pos != string::npos) {
			v.push_back(str.substr(seek, pos - seek));
			seek = pos + 1;
		}
		else {
			v.push_back(str.substr(seek));
			seek = str.length();
		}
	}

	return v;
}

float degToRad(float x) {
	return x * 0.01745329251944444444444444444444;
}

float radToDeg(float x) {
	return x * 57.295779514719953173585430909526;
}