#include "Shape.h"
#include "Intersection.h"
#include "Ray.h"

Tuple Shape::normal_at(const Tuple &p)
{
    Matrix tempInversedTransform = inversedTransform;

    Tuple local_point = inversedTransform * p;
    Tuple local_normal = local_normal_at(local_point);
    Tuple world_normal = tempInversedTransform.transpose() * local_normal;
    world_normal.w = 0;

    return normalize(world_normal);
}

IntersectionList Shape::intersect(Ray &r)
{
    Ray lr = r.transform(inversedTransform);
    return local_intersect(lr);
}

void Shape::setTransform(Matrix n)
{
    transform = n;
    inversedTransform = n.inverse();
}

Matrix Shape::getTransform() const
{
    return this->transform;
}

Matrix Shape::getInversedTransform()
{
    return this->inversedTransform;
}
