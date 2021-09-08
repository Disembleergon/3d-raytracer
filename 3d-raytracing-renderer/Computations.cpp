#include "Computations.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"
#include <algorithm>

#define EPSILON 0.00001

Computations prepare_computations(Intersection i, Ray r, std::vector<Intersection> xs)
{

    Tuple point = r.position(i.t);
    Tuple eyev = r.direction() * -1;
    Tuple normalv = i.object->normal_at(point);
    bool inside = false;

    // if normal vector and eye vector point in opposite directions: eye inside of sphere
    if (dot(normalv, eyev) < 0)
    {
        inside = true;
        normalv = normalv * -1;
    }

    Tuple overpoint = point + normalv * EPSILON;
    Tuple underpoint = point - normalv * EPSILON;
    Tuple reflectv = reflect(r.direction(), normalv);

    std::vector<Shape *> containers{};
    double n1 = 0;
    double n2 = 0;

    for (auto &xsi : xs)
    {
        if (xsi == i)
        {
            if (containers.empty())
                n1 = 1.0;
            else
                n1 = containers.back()->material.refractive_index;
        }

        bool found = false;

        for (auto it = containers.begin(); it != containers.end(); it++)
        {
            if (*it == xsi.object)
            {
                containers.erase(it);
                found = true;
                break;
            }
        }

        if (!found)
            containers.push_back(xsi.object);

        if (xsi == i)
        {
            if (containers.empty())
                n2 = 1;
            else
                n2 = containers.back()->material.refractive_index;

            break;
        }
    }

    return Computations{i.t, i.object, point, eyev, normalv, inside, overpoint, underpoint, reflectv, n1, n2};
}
