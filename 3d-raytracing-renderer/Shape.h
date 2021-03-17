#pragma once
#include "Material.h"
#include "Matrix.h"
#include <vector>

class Intersection;
class Ray;
class Tuple;

struct Shape
{

    Matrix transform = IDENTITY_MATRIX();
    Material material{};

    void operator=(const Shape *&sp)
    {
        transform = sp->transform;
        material = sp->material;
    }

    bool operator==(const Shape *&sp)
    {
        return material == sp->material && transform == sp->transform;
    }

    Tuple normal_at(const Tuple &);
    std::vector<Intersection> intersect(Ray);
    virtual std::vector<Intersection> local_intersect(Ray) = 0;
    virtual Tuple local_normal_at(const Tuple &) = 0;
};
