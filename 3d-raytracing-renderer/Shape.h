#pragma once
#include "Material.h"
#include "Matrix.h"
#include <vector>

static int shape_count{0};

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
    const int shape_id{++shape_count};

    virtual ~Shape() = default;
    Shape() = default;

    void operator=(Shape *sp)
    {
        setTransform(sp->getTransform());
        material = sp->material;
    }

    bool operator==(Shape &sp)
    {
        return shape_id == sp.shape_id;
    }

    Tuple normal_at(const Tuple &);
    std::vector<Intersection> intersect(Ray &);
    virtual std::vector<Intersection> local_intersect(Ray) = 0;
    virtual Tuple local_normal_at(const Tuple &) = 0;
    void setTransform(Matrix);
    Matrix getTransform();
    Matrix getInversedTransform();
};
