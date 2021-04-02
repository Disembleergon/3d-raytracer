#include "World.h"
#include "Camera.h"
#include "Canvas.h"
#include "Computations.h"
#include "Intersection.h"
#include "Progressbar.hpp"
#include "Ray.h"

//Color reflected_color(World &w, Computations &comps, int remaining);

Color shade_hit(World &world, Computations &comps, const int& remaining)
{
    bool shadowed = is_shadowed(world, comps.over_point);
    auto surface =
        lighting(comps.object->material, comps.object, world.light, comps.point, comps.eyev, comps.normalv, shadowed);
    auto reflected = reflected_color(world, comps, remaining);

    return surface + reflected;
}

Color color_at(World &world, Ray &r, const int remaining)
{
    IntersectionList xs = r.intersect_world(world);
    Intersection i = hit(xs);

    if (!i.isDefined())
        return Color{};

    Computations tcomps = prepare_computations(i, r);
    return shade_hit(world, tcomps, remaining);
}

Canvas World::render(Camera &cam)
{
    progresscpp::ProgressBar pb(cam.hsize * cam.vsize, 70);

    Canvas image{cam.hsize, cam.vsize};
    for (int y = 0; y < cam.vsize; y++)
    {
        for (int x = 0; x < cam.hsize; x++)
        {
            Ray r = cam.ray_for_pixel(x, y);
            Color clr = color_at(*this, r, 4);

            image.write_pixel(x, y, clr.normize());
            ++pb;
            pb.display();
        }
    }

    pb.done();
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

Color reflected_color(World &w, Computations &comps, const int& remaining)
{

    if (remaining <= 0)
        return Color{}; // black

    if (comps.object->material.reflective == 0)
        return Color{}; // black

    Ray reflect_ray{comps.over_point, comps.reflectv};
    Color clr = color_at(w, reflect_ray, remaining-1);

    return clr * comps.object->material.reflective;
}
