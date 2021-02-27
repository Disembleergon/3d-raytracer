#pragma once
#include "Tuple.h"
#include "Shape.h"
#include "Intersection.h"
#include "Matrix.h"
#include "World.h"
#include <vector>

class World;
using scalar_t = double;

class Ray {

private:
	const Tuple m_origin;
	const Tuple m_direction;
public:

	Ray(const Tuple& origin, const Tuple& direction)
		: m_origin{ origin }, m_direction{ direction }{}

	Tuple origin() const {
		return m_origin;
	}

	Tuple direction() const {
		return m_direction;
	}

	Tuple position(const scalar_t& t) const {
		return m_origin + m_direction * t;
	}

	Ray transform(Matrix m) {
		return Ray{ m * m_origin, m * m_direction };
	}

	IntersectionList intersect(Shape&);

	IntersectionList intersect_world(World);

};