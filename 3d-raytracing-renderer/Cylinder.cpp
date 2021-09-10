#include "Cylinder.h"
#include "Intersection.h"
#include "Ray.h"

bool Cylinder::check_cap(member_t t, Ray r) const
{
    const auto x = r.origin().x + t * r.direction().x;
    const auto z = r.origin().z + t * r.direction().z;

    return std::pow(x, 2) + std::pow(z, 2) <= 1;
}

void Cylinder::intersect_caps(Ray r, IntersectionList &xs)
{
    // caps only matter if the cylinder is closed, and might possibly be
    // intersected by the ray
    if (!closed || floatEqual(r.direction().y, 0))
        return;

    // check for an intersection with the lower end cap by intersecting
    // the ray with the plane at y = cyl.minimum
    member_t t = (minimum - r.origin().y) / r.direction().y;
    if (check_cap(t, r))
        xs.push_back(Intersection{t, this});

    // check for an intersection with the upper end cap by intersecting
    // the ray with the plane at y = cyl.maximum
    t = (maximum - r.origin().y) / r.direction().y;
    if (check_cap(t, r))
        xs.push_back(Intersection{t, this});
}

std::vector<Intersection> Cylinder::local_intersect(Ray ray)
{
    const auto a = std::pow(ray.direction().x, 2) + std::pow(ray.direction().z, 2);
    IntersectionList xs{};

    // ray is parallel to the y axis
    if (floatEqual(a, 0))
    {
        intersect_caps(ray, xs);
        return xs;
    }

    const auto b = 2 * ray.origin().x * ray.direction().x + 2 * ray.origin().z * ray.direction().z;
    const auto c = std::pow(ray.origin().x, 2) + std::pow(ray.origin().z, 2) - 1;
    const auto disc = std::pow(b, 2) - 4 * a * c;

    // ray does not intersect the cylinder
    if (disc < 0)
        return {};

    auto t0 = (-b - std::sqrt(disc)) / (2 * a);
    auto t1 = (-b + std::sqrt(disc)) / (2 * a);

    if (t0 > t1)
        std::swap(t0, t1);

    // truncate cylinder

    const auto y0 = ray.origin().y + t0 * ray.direction().y;
    if (minimum < y0 && y0 < maximum)
        xs.push_back(Intersection{t0, this});

    const auto y1 = ray.origin().y + t1 * ray.direction().y;
    if (minimum < y1 && y1 < maximum)
        xs.push_back(Intersection{t1, this});

    intersect_caps(ray, xs);
    return xs;
}

Tuple Cylinder::local_normal_at(const Tuple &p)
{
    const auto dist = std::pow(p.x, 2) + std::pow(p.z, 2);

    if (dist < 1)
    {
        if (p.y >= maximum - EPSILON)
            return vector(0, 1, 0);
        if (p.y <= minimum + EPSILON)
            return vector(0, -1, 0);
    }

    return vector(p.x, 0, p.z);
}
