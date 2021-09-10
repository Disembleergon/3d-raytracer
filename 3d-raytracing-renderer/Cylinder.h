#pragma once
#include "Shape.h"

class Cylinder : public Shape
{
  private:
    using member_t = double;
    using IntersectionList = std::vector<Intersection>;

    bool check_cap(member_t t, Ray r) const;
    void intersect_caps(Ray r, IntersectionList &xs);

  public:
    Cylinder() = default;

    member_t minimum{-INFINITY};
    member_t maximum{INFINITY};
    bool closed{false};

    std::vector<Intersection> local_intersect(Ray) override;
    Tuple local_normal_at(const Tuple &) override;
};
