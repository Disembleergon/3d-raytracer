#include "Ray.h"
#include "Intersection.h"
#include "Shape.h"
#include "World.h"

#include <algorithm>
#include <cmath>
#include <iostream>

IntersectionList Ray::intersect_world(World &world)
{

    IntersectionList xs;

    for (int i = 0; i < world.objects.size(); i++)
    {

        IntersectionList xxs = world.objects[i]->intersect(*this);

        if (xxs.size() != 0)
        {
            xs.push_back(xxs.at(0));
            if (xxs.size() == 1)
            {
                xs.push_back(xxs.at(0));
                continue;
            }

            xs.push_back(xxs.at(1));
        }
    }

    std::sort(xs.begin(), xs.end()); // fixed

    return xs;
}
