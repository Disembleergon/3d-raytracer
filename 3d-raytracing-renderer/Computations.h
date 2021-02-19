#pragma once
#include "Ray.h"
#include "Shape.h"
#include "Tuple.h"
#include "Intersection.h"

class Ray;

struct Computations {

	double t;
	Shape object;
	Tuple point;
	Tuple eyev;
	Tuple normalv;
	bool inside;

};

Computations prepare_computations(Intersection i, Ray r);