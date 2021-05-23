#pragma once
#include <memory>
#include <vector>

#include "Matrix.h"
#include "PointLight.h"
#include "Shape.h"
#include "Sphere.h"

// class Shape;
class Computations;
class Ray;
class Canvas;
class Camera;

struct World
{
    std::vector<std::unique_ptr<Shape>> objects{};
    PointLight light;

    World() = default;

    //World &operator=(const World &) = delete;
    //World(const World &) = delete;

    Canvas render(Camera &);

    template <class ShapeType> void addShape(const ShapeType &shape)
    {
        objects.emplace_back(std::make_unique<ShapeType>(shape));
    }
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
    s2.setTransform(scaling(0.5, 0.5, 0.5));

    out.addShape<Sphere>(s1);
    out.addShape<Sphere>(s2);

    return out;
}

// calculate lighting with computations
Color shade_hit(World &world, Computations &comps, const int &remaining);

// bring everything together (calculating color based on a ray and the world)
Color color_at(World &world, Ray &r, const int remaining = 4);

bool is_shadowed(World &world, Tuple &p);

// reflection algorithm
Color reflected_color(World &, Computations &, const int &remaining);
