#pragma once
#define EPSILON 0.00001
#include <math.h>

inline bool floatEqual(float a, float b) {
	return (abs(a - b) < EPSILON);
}