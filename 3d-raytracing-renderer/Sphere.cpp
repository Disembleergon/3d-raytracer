#include "Sphere.h"
#include "Intersection.h"
#include "Ray.h"
#include "Tuple.h"

IntersectionList Sphere::local_intersect(Ray r)
{
    IntersectionList intersections;

    /*the vector from the sphere's center, to the ray origin
    remember: the sphere is centered at the world origin*/
    Tuple sphere_to_ray = r.origin() - point(0, 0, 0);

    scalar_t a = dot(r.direction(), r.direction());
    scalar_t b = 2 * (dot(r.direction(), sphere_to_ray));
    scalar_t c = (dot(sphere_to_ray, sphere_to_ray) - 1);
    scalar_t discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant < 0) // wenn negativ: Ray verfehlt Sphere
        return intersections;

    // Reihenfolge: aufsteigend
    intersections.push_back(Intersection{((-b - sqrt(discriminant)) / (2 * a)), this});
    intersections.push_back(Intersection{((-b + sqrt(discriminant)) / (2 * a)), this});
    // std::sort(intersections.begin(), intersections.end());

    return intersections;
}

Tuple Sphere::local_normal_at(const Tuple &p)
{
    return p - point(0, 0, 0);
}
