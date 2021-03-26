#pragma once
#define EPSILON 0.00001
#include <math.h>

inline bool floatEqual(double a, double b) {
	return (fabs(a - b) < EPSILON);
}