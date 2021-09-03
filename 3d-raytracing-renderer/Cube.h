#pragma once
#include "Shape.h"

class Cube : public Shape
{
  public:
    Cube() = default;

    std::vector<Intersection> local_intersect(Ray) override;
    Tuple local_normal_at(const Tuple &) override;

  private:
    std::tuple<double, double> check_axis(const double origin, const double direction) const;
};
