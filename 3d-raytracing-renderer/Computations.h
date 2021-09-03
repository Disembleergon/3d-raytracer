#pragma once
#include "Shape.h"
#include "Tuple.h"

class Intersection;
class Ray;

class Computations
{
  public:
    double t;
    Shape *object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
    Tuple over_point;
    Tuple under_point;
    Tuple reflectv;
    double n1;
    double n2;
};

Computations prepare_computations(Intersection i, Ray r, std::vector<Intersection> xs);
