#include "Computations.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

#define EPSILON 0.00001

Computations prepare_computations(Intersection i, Ray r)
{

    Tuple point = r.position(i.t);
    Tuple eyev = r.direction() * -1;
    Tuple normalv = i.object.normal_at(point);
    Tuple overpoint = point + normalv * EPSILON;
    bool inside = false;

    // if normal vector and eye vector point in opposite directions: eye inside of sphere
    if (dot(normalv, eyev) < 0)
    {
        inside = true;
        normalv = normalv * -1;
    }

    return Computations{i.t, i.object, point, eyev, normalv, inside, overpoint};
}
