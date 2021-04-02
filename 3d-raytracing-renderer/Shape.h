#pragma once
#include "Material.h"
#include "Matrix.h"
#include <vector>

class Intersection;
class Ray;
class Tuple;

class Shape
{
  private:
    Matrix transform = IDENTITY_MATRIX();
    Matrix inversedTransform = IDENTITY_MATRIX();

  public:
    Material material{};

    void operator=(Shape *sp)
    {
        setTransform(sp->getTransform());
        material = sp->material;
    }

    bool operator==(Shape *sp)
    {
        return material == sp->material && transform == sp->getTransform();
    }

    Tuple normal_at(const Tuple &);
    std::vector<Intersection> intersect(Ray);
    virtual std::vector<Intersection> local_intersect(Ray) = 0;
    virtual Tuple local_normal_at(const Tuple &) = 0;
    void setTransform(Matrix);
    Matrix getTransform();
    Matrix getInversedTransform();
};
