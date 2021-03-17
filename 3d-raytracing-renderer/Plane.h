#pragma once
#include "Shape.h"
#include <vector>

class Intersection;
class Ray;
class Tuple;

struct Plane : public Shape
{
    std::vector<Intersection> local_intersect(Ray) override;
    Tuple local_normal_at(const Tuple &) override;
};
