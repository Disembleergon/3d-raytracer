#include "Cube.h"
#include "Equal.h"
#include "Intersection.h"
#include "Ray.h"

#include <algorithm>
#include <math.h>

std::vector<Intersection> Cube::local_intersect(Ray r)
{
    const auto [xtmin, xtmax] = check_axis(r.origin().x, r.direction().x);
    const auto [ytmin, ytmax] = check_axis(r.origin().y, r.direction().y);
    const auto [ztmin, ztmax] = check_axis(r.origin().z, r.direction().z);

    const auto tmin = std::max({xtmin, ytmin, ztmin});
    const auto tmax = std::min({xtmax, ytmax, ztmax});

    if (tmin > tmax)
        return {};

    return {Intersection{tmin, this}, Intersection{tmax, this}};
}

Tuple Cube::local_normal_at(const Tuple &p)
{
    const auto absX = std::abs(p.x);
    const auto absY = std::abs(p.y);
    const auto maxc = std::max({absX, absY, std::abs(p.z)});

    if (floatEqual(maxc, absX))
        return vector(p.x, 0, 0);
    else if (floatEqual(maxc, absY))
        return vector(0, p.y, 0);

    return vector(0, 0, p.z);
}

std::tuple<double, double> Cube::check_axis(const double origin, const double direction) const
{
    const auto tmin_numerator = (-1 - origin);
    const auto tmax_numerator = (1 - origin);

    double tmin;
    double tmax;

    if (std::abs(direction) >= EPSILON)
    {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    }
    else
    {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax)
        std::swap(tmin, tmax);

    return std::make_tuple(tmin, tmax);
}
