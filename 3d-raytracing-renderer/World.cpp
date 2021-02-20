#include "World.h"
#include "Intersection.h"
#include "Progressbar.hpp"
#include "Ray.h"

Color shade_hit(World &world, Computations &comps)
{
    Color temp{};

    for (int i = 0; i < world.lights.size(); i++)
    {
        temp = temp + lighting(comps.object.material, world.lights[i], comps.point, comps.eyev, comps.normalv);
    }

    return temp;
    // return lighting(comps.object.material, world.lights[0], comps.point, comps.eyev, comps.normalv);
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

            image.write_pixel(x, y, clr.normize(1, 1, 1));
            ++pb;
            pb.display();
        }
    }

    pb.done();
    return image;
}
