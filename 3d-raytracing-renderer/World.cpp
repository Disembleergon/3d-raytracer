#include "World.h"

#include <fstream>

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
    std::ofstream out("C:\\Users\\tompe\\desktop\\highest_values.txt");
    double red_max = 0;
    double green_max = 0;
    double blue_max = 0;
    bool first_time = true;
    progresscpp::ProgressBar pb(cam.hsize * cam.vsize, 70);

    for (int y = 0; y < cam.vsize; y++)
    {
        for (int x = 0; x < cam.hsize; x++)
        {
            Ray r = cam.ray_for_pixel(x, y);
            Color clr = color_at(*this, r);

            red_max = first_time ? clr.red : std::max(red_max, clr.red);
            green_max = first_time ? clr.green : std::max(green_max, clr.green);
            blue_max = first_time ? clr.blue : std::max(blue_max, clr.blue);
            first_time = false;
            out << "r: " << red_max << " ; g: " << green_max << " ; b: " << blue_max << std::endl;
        }
    }

    Canvas image{cam.hsize, cam.vsize};
    for (int y = 0; y < cam.vsize; y++)
    {
        for (int x = 0; x < cam.hsize; x++)
        {
            Ray r = cam.ray_for_pixel(x, y);
            Color clr = color_at(*this, r);

            image.write_pixel(x, y, clr.normize(red_max, green_max, blue_max));
            ++pb;
            pb.display();
        }
    }

    out.close();
    pb.done();
    return image;
}
