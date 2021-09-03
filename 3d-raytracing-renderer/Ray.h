#pragma once
#include "Matrix.h"
#include "Tuple.h"
#include <vector>

class Shape;
class World;
class Intersection;

using member_t = double;

class Ray
{

  private:
    const Tuple m_origin;
    const Tuple m_direction;

  public:
    Ray(const Tuple &origin, const Tuple &direction) : m_origin{origin}, m_direction{direction}
    {
    }

    Tuple origin() const
    {
        return m_origin;
    }

    Tuple direction() const
    {
        return m_direction;
    }

    Tuple position(const member_t &t) const
    {
        return m_origin + m_direction * t;
    }

    Ray transform(Matrix m)
    {
        // 14356594x1435694
        return Ray{m * m_origin, m * m_direction};
    }

	std::vector<Intersection> intersect_world(World&);

};