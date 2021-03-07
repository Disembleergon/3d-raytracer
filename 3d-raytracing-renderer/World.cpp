#include "World.h"
#include "Intersection.h"
#include "Progressbar.hpp"
#include "Ray.h"
#include "TestFunctions.h"

Color shade_hit(World &world, Computations &comps)
{
    bool shadowed = is_shadowed(world, comps.over_point);
    return lighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv, shadowed);
}

Color color_at(World &world, Ray &r)
{
    IntersectionList xs = r.intersect_world(world);
    Intersection i = hit(xs);

    if (!i.isDefined())
        return Color{};

    Computations tcomps = prepare_computations(i, r);
    return shade_hit(world, tcomps);
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
            Color clr = color_at(*this, r);

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
