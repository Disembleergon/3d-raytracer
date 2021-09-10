#pragma once
#define EPSILON 0.00001
#include <cmath>

inline bool floatEqual(double a, double b) {
	return (fabs(a - b) < EPSILON);
}