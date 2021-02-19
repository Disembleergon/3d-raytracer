#include "Computations.h"

Computations prepare_computations(Intersection i, Ray r) {

	Tuple point = r.position(i.t);
	Tuple eyev = r.direction() * -1;
	Tuple normalv = i.object.normal_at(point);
	bool inside = false;

	// if normal vector and eye vector point in opposite directions: eye inside of sphere
	if (dot(normalv, eyev) < 0) {
		inside = true;
		normalv = normalv * -1;
	}

	return Computations{ i.t, i.object, point, eyev, normalv, inside };

}