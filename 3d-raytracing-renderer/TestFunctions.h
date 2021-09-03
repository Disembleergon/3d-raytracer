#pragma once
#define _USE_MATH_DEFINES
#define EPSILON 0.00001

#include <iostream>
#include <math.h>

#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Computations.h"
#include "Cube.h"
#include "Equal.h"
#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
#include "Patterns.h"
#include "Plane.h"
#include "PointLight.h"
#include "Ray.h"
#include "Tuple.h"
#include "World.h"

namespace TESTS
{

inline void printMatrix(const Matrix &mat)
{
    for (int row = 0; row < mat.rows(); row++)
    {
        for (int col = 0; col < mat.cols(); col++)
        {
            std::cout << mat.get(row, col) << " | ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

inline void printTuple(const Tuple &tup)
{
    std::cout << "x: " << tup.x << " y: " << tup.y << " z: " << tup.z << " w: " << tup.w << std::endl;
    std::cout << std::endl;
}

inline void printColor(const Color &clr)
{
    std::cout << "r: " << clr.red << " g: " << clr.green << " b: " << clr.blue << std::endl;
    std::cout << std::endl;
}

template <typename T> inline void printVector(std::vector<T> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
}

template <typename T> inline void printArray(T arr[], const int &size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
}

inline void printRay(const Ray &r)
{
    std::cout << "origin:\n";
    TESTS::printTuple(r.origin());
    std::cout << "direction:\n";
    TESTS::printTuple(r.direction());
    std::cout << std::endl;
}

inline void printMaterial(const Material &mat)
{
    std::cout << "Color:\n";
    TESTS::printColor(mat.color);
    std::cout << "ambient: " << mat.ambient << " ; diffuse: " << mat.diffuse << " ; specular: " << mat.specular
              << " ; shininess: " << mat.shininess << "\n";
}

inline void printLight(const PointLight &light)
{
    std::cout << "pos:\n";
    TESTS::printTuple(light.position);
    std::cout << "intensity:\n";
    TESTS::printColor(light.intensity);
}

inline void printIntersection(Intersection i)
{
    if (i.isDefined())
        std::cout << "t: " << i.t << std::endl;
    else
        std::cout << "t: NULL" << std::endl;
}

inline void printIntersectionList(const IntersectionList &xs)
{
    std::cout << "size of IntersectionList: " << xs.size() << std::endl;
    for (Intersection i : xs)
        printIntersection(i);
}

inline void printComputations(const Computations &cp)
{
    std::cout << "eyev:\n";
    TESTS::printTuple(cp.eyev);
    std::cout << "normalv:\n";
    TESTS::printTuple(cp.normalv);
    std::cout << "point:\n";
    TESTS::printTuple(cp.point);
    std::cout << "overpoint:\n";
    TESTS::printTuple(cp.over_point);
    std::cout << "t: " << cp.t << std::endl;
    std::cout << "inside? " << cp.inside << "\n\n";
    std::cout << "reflectv: " << std::endl;
    TESTS::printTuple(cp.reflectv);
}

inline void printCamera(Camera &cam)
{
    std::cout << "hsize: " << cam.hsize << " ; vsize: " << cam.vsize << " ; fov: " << cam.fov
              << " ; half_width: " << cam.half_width << " ; half_height: " << cam.half_height
              << " ; pixel size: " << cam.pixel_size << " ; transform:\n";
    TESTS::printMatrix(cam.getTransformation());
}

inline void renderTest()
{
    /*World w{};

    Plane wall{};
    wall.setTransform(translation(0, 0, 10) * rotate_x(1.5708));

    SolidPattern clrA{Color{0.15, 0.15, 0.15}};
    SolidPattern clrB{Color{0.85, 0.85, 0.85}};
    CheckersPattern checkers{makePattern_ptr<SolidPattern>(clrA), makePattern_ptr<SolidPattern>(clrB)};
    wall.material.pattern = makePattern_ptr<CheckersPattern>(checkers);

    wall.material.ambient = 0.8;
    wall.material.diffuse = 0.2;
    wall.material.specular = 0;
    w.addShape<Plane>(wall);

    Sphere glassSphere{};

    Material glass{};
    glass.color = Color{1, 1, 1};
    glass.ambient = 0;
    glass.diffuse = 0;
    glass.specular = 0.9;
    glass.shininess = 300;
    glass.reflective = 0.9;
    glass.transparency = 0.9;
    glass.refractive_index = RefractiveIndex::glass;

    glassSphere.material = glass;
    w.addShape<Sphere>(glassSphere);

    Material hollow{};
    hollow.color = Color{1, 1, 1};
    hollow.ambient = 0;
    hollow.diffuse = 0;
    hollow.specular = 0.9;
    hollow.shininess = 300;
    hollow.reflective = 0.9;
    hollow.transparency = 0.9;
    hollow.refractive_index = 1.0000034;

    Sphere hollowSphere{};
    hollowSphere.setTransform(scaling(0.5, 0.5, 0.5));
    hollowSphere.material = hollow;
    w.addShape<Sphere>(hollowSphere);

    w.light = PointLight{point(2, 10, -5), Color{0.9, 0.9, 0.9}};

    Camera cam{300, 300, .45};
    cam.setTransformation(view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");*/

    // ----------------- room with table and a mirror -------------------

    World w{};

    Material table{};
    table.color = highvalueColor(125, 84, 84);

    SolidPattern brown{highvalueColor(117, 77, 75)};
    SolidPattern darkbrown{highvalueColor(87, 59, 58)};
    StripePattern wooden{makePattern_ptr<SolidPattern>(brown), makePattern_ptr<SolidPattern>(darkbrown)};
    wooden.setTransform(scaling(0.2, 0.2, 0.2));

    Material room{};
    // room.color = highvalueColor(194, 194, 194);
    room.shininess = 300;
    room.pattern = makePattern_ptr<StripePattern>(wooden);

    // underground pattern
    SolidPattern red{highvalueColor(240, 43, 36)};
    SolidPattern white{highvalueColor(209, 175, 174)};
    CheckersPattern undergroundCheckers{makePattern_ptr<SolidPattern>(red), makePattern_ptr<SolidPattern>(white)};

    Plane underground{};
    underground.material = room;
    underground.material.pattern = makePattern_ptr<CheckersPattern>(undergroundCheckers);
    underground.material.reflective = 0.2;
    w.addShape<Plane>(underground);

    Plane wall1{};
    wall1.material = room;
    wall1.setTransform(translation(-5, 0, 5) * rotate_y(toRadians(-45)) * rotate_x(toRadians(-90)));
    w.addShape<Plane>(wall1);

    Plane wall2{};
    wall2.material = room;
    wall2.setTransform(translation(5, 0, 5) * rotate_y(toRadians(45)) * rotate_x(toRadians(-90)));
    w.addShape<Plane>(wall2);

    Cube tablePart1{};
    tablePart1.setTransform(translation(-1, 0, 1) * scaling(0.1, 0.7, 0.1));
    tablePart1.material = table;
    w.addShape<Cube>(tablePart1);

    Cube tablePart2{};
    tablePart2.setTransform(translation(1, 0, 1) * scaling(0.1, 0.7, 0.1));
    tablePart2.material = table;
    w.addShape<Cube>(tablePart2);

    Cube tablePart3{};
    tablePart3.setTransform(translation(-1, 0, 0) * scaling(0.1, 0.7, 0.1));
    tablePart3.material = table;
    w.addShape<Cube>(tablePart3);

    Cube tablePart4{};
    tablePart4.setTransform(translation(1, 0, 0) * scaling(0.1, 0.7, 0.1));
    tablePart4.material = table;
    w.addShape<Cube>(tablePart4);

    Cube tableTop{};
    tableTop.setTransform(translation(0, 0.8, 0.6) * scaling(1.2, 0.1, 0.7));
    tableTop.material = table;
    w.addShape<Cube>(tableTop);

    Cube mirror{};
    mirror.material.reflective = 1;
    mirror.material.diffuse = 0;
    mirror.material.ambient = 0;
    mirror.material.shininess = 300;
    mirror.material.color = Color{1, 1, 1};
    mirror.setTransform(translation(4, 1.4, 6.1) * rotate_y(toRadians(45)) * scaling(2, 1, 0.1));
    w.addShape<Cube>(mirror);

    w.light = PointLight{point(2, 5, -5), Color{1, 1, 1}};

    Camera cam{4000, 2000, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 2, -5), point(0, 1, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");
}

} // namespace TESTS
