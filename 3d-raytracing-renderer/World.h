#pragma once
#include "Camera.h"
#include "Canvas.h"
#include "Computations.h"
#include "PointLight.h"
#include "Ray.h"
#include "Shape.h"
#include "Sphere.h"
#include <vector>

class Computations;
class Ray;
class Camera;

struct World
{

    std::vector<Shape> objects;
    PointLight light;

    Canvas render(Camera &);
};

inline World DEFAULT_WORLD()
{

    World out{};
    out.light = PointLight{point(-10, 10, -10), Color{1, 1, 1}};

    Sphere s1{};
    Material m1{};
    m1.color = Color{0.8, 1.0, 0.6};
    m1.diffuse = 0.7;
    m1.specular = 0.2;
    s1.material = m1;

    Sphere s2{};
    s2.transform = scaling(0.5, 0.5, 0.5);

    out.objects.push_back(s1);
    out.objects.push_back(s2);

    return out;
}

// calculate lighting with computations
Color shade_hit(World &world, Computations &comps);

// bring everything together (calculating color based on a ray and the world)
Color color_at(World &world, Ray &r);

bool is_shadowed(World &world, Tuple &p);