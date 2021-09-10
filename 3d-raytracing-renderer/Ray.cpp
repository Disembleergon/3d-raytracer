#include "Ray.h"
#include "Intersection.h"
#include "Shape.h"
#include "World.h"

#include <algorithm>
#include <iostream>
#include <cmath>

IntersectionList Ray::intersect_world(World& world)
{

    IntersectionList xs;

    for (int i = 0; i < world.objects.size(); i++)
    {

        IntersectionList xxs = world.objects[i]->intersect(*this);

        if (xxs.size() != 0)
        {
            xs.push_back(xxs[0]);
            xs.push_back(xxs[1]);
        }
    }

    std::sort(xs.begin(), xs.end()); // fixed

    return xs;
}
