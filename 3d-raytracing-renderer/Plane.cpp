#include "Plane.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

#include <math.h>
#define EPSILON 0.00001

IntersectionList Plane::local_intersect(Ray r)
{
    if (abs(r.direction().y) < EPSILON)
        return {};

    auto t = (-r.origin().y) / r.direction().y;
    return {Intersection{t, this}, Intersection{t, this}};
}

Tuple Plane::local_normal_at(const Tuple &p)
{
    return vector(0, 1, 0);
}
