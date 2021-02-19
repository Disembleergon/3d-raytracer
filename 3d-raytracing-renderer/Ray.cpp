#include "Ray.h"
#include "TestFunctions.h"
#include <math.h>
#include <algorithm>
#include <iostream>

IntersectionList Ray::intersect(Shape& sp) {

	Ray r = transform(sp.transform.inverse());
	IntersectionList intersections;

	/*the vector from the sphere's center, to the ray origin
	remember: the sphere is centered at the world origin*/
	Tuple sphere_to_ray = r.origin() - point(0, 0, 0);

	scalar_t a = dot(r.direction(), r.direction());
	scalar_t b = 2 * (dot(r.direction(), sphere_to_ray));
	scalar_t c = (dot(sphere_to_ray, sphere_to_ray) - 1);
	scalar_t discriminant = b * b - 4 * a * c;

	if (discriminant < 0)	// wenn negativ: Ray verfehlt Sphere
		return intersections;

	// Reihenfolge: aufsteigend
	intersections.push_back(Intersection{ ((-b - sqrt(discriminant)) / (2 * a)), sp });
	intersections.push_back(Intersection{ ((-b + sqrt(discriminant)) / (2 * a)), sp });

	return intersections;
}

IntersectionList Ray::intersect_world(World& world) {

	IntersectionList xs;

	for (Shape s : world.objects) {

		IntersectionList xxs = intersect(s);
		if (xxs.size() != 0) {
			xs.push_back(xxs[0]);
			xs.push_back(xxs[1]);
		}
	}

	std::sort(xs.begin(), xs.end());
	return xs;
}
