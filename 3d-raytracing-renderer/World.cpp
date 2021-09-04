#include "World.h"
#include "Camera.h"
#include "Canvas.h"
#include "Computations.h"
#include "Equal.h"
#include "Intersection.h"
#include "Ray.h"
#include <iostream>

Color shade_hit(World &world, Computations &comps, const int &remaining)
{
    const bool shadowed = is_shadowed(world, comps.over_point);
    const auto surface = lighting(comps.object->material, comps.object, world.light, comps.over_point, comps.eyev,
                                  comps.normalv, shadowed);
    const auto reflected = reflected_color(world, comps, remaining);
    const auto refracted = refracted_color(world, comps, remaining);

    if (comps.object->material.reflective > 0 && comps.object->material.transparency > 0)
    {
        const auto reflectance = schlick(comps);
        return surface + reflected * reflectance + refracted * (1 - reflectance);
    }

    return surface + reflected + refracted;
}

Color color_at(World &world, Ray &r, const int remaining)
{
    IntersectionList xs = r.intersect_world(world);
    Intersection i = hit(xs);

    if (!i.isDefined())
        return Color{};

    Computations tcomps = prepare_computations(i, r, xs);
    return shade_hit(world, tcomps, remaining);
}

Canvas World::render(Camera &cam)
{
    Canvas image{cam.hsize, cam.vsize};
    for (int y = 0; y < cam.vsize; y++)
    {
        for (int x = 0; x < cam.hsize; x++)
        {
            Ray r = cam.ray_for_pixel(x, y);
            Color clr = color_at(*this, r, 4);
            image.write_pixel(x, y, clr.normize());
        }
    }
    return image;
}

bool is_shadowed(World &world, Tuple &p)
{
    Tuple v = world.light.position - p;
    auto distance = magnitude(v);
    Tuple direction = normalize(v);

    Ray r{p, direction};
    IntersectionList intersections = r.intersect_world(world);
    Intersection h = hit(intersections);

    if (h.isDefined() && h.t < distance)
        return true;
    return false;
}

Color reflected_color(World &w, Computations &comps, const int remaining)
{
    if (remaining <= 0)
        return Color{}; // black

    if (comps.object->material.reflective == 0)
        return Color{}; // black

    Ray reflect_ray{comps.over_point, comps.reflectv};
    Color clr = color_at(w, reflect_ray, remaining - 1);

    return clr * comps.object->material.reflective;
}

Color refracted_color(World &w, Computations &comps, const int remaining)
{
    if (floatEqual(comps.object->material.transparency, 0) || remaining <= 0)
        return Color{}; // black

    // --------- total internal reflection handling -----------

    // Find the ratio of first index of refraction to the second.
    // (this is inverted from the definition of Snell's Law.)
    const double n_ratio = comps.n1 / comps.n2;

    // cos(theta_i) is the same as the dot product of the two vectors
    const auto cos_i = dot(comps.eyev, comps.normalv);

    // Find sin(theta_t)^2 via trigonometric identity
    const double sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));

    if (sin2_t > 1)     // total internal reflection
        return Color{}; // black

    // ------ finding the refracted color --------

    // Find cos(theta_t) via trigonometric identity
    const double cos_t = std::sqrt(1.0 - sin2_t);

    // Compute the direction of the refracted ray
    const Tuple direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;
    Ray refractRay{comps.under_point, direction};

    return color_at(w, refractRay, remaining - 1) * comps.object->material.transparency;
}

double schlick(Computations &comps)
{
    auto cos = dot(comps.eyev, comps.normalv);

    if (comps.n1 > comps.n2)
    {
        const auto n = comps.n1 / comps.n2;
        const auto sin2_t = std::pow(n, 2) * (1.0 - std::pow(cos, 2));

        if (sin2_t > 1.0)
            return 1.0;

        const auto cos_t = std::sqrt(1.0 - sin2_t);
        cos = cos_t;
    }

    const auto r0 = std::pow((comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2);

    return r0 + (1 - r0) * std::pow((1 - cos), 5);
}
