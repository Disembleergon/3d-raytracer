#pragma once
#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"
#include "Tuple.h"

class Ray;

struct Computations
{
    double t;
    Shape object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
    Tuple over_point;
};

Computations prepare_computations(Intersection i, Ray r);
