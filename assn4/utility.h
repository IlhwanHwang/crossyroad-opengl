//
// BetterCarryingEachOther 2016.03.15
// utility functions
//

#pragma once

#include <vector>
#include "vec.h"

using namespace std;

float frand();
float frandRange(float a, float b);
float flerp(float a, float b, float x);
vec3 lerpv3(vec3 a, vec3 b, float x);
vector<string> tokenize(string str, string delim);
float degToRad(float x);
float radToDeg(float x);