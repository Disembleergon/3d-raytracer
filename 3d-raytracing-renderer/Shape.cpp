#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

Tuple Shape::normal_at(const Tuple &p)
{
    Tuple local_point = transform.inverse() * p;
    Tuple local_normal = local_normal_at(local_point);
    Tuple world_normal = transform.inverse().transpose() * local_normal;
    world_normal.w = 0;

    return normalize(world_normal);
}

IntersectionList Shape::intersect(Ray r)
{
    Ray lr = r.transform(transform.inverse());
    return this->local_intersect(lr);
}
