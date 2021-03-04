#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#include <fstream>
#include <iostream>

#include "Camera.h"
#include "Canvas.h"
#include "Color.h"
#include "Computations.h"
#include "Equal.h"
#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
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
    std::cout << "t: " << cp.t << std::endl;
    std::cout << "inside? " << cp.inside << "\n\n";
}

inline void printCamera(const Camera &cam)
{
    std::cout << "hsize: " << cam.hsize << " ; vsize: " << cam.vsize << " ; fov: " << cam.fov
              << " ; half_width: " << cam.half_width << " ; half_height: " << cam.half_height
              << " ; pixel size: " << cam.pixel_size << " ; transform:\n";
    TESTS::printMatrix(cam.transform);
}

inline void CanvasTest()
{
    World world{};

    Sphere floor{};
    floor.transform = scaling(10, 0.01, 10);
    floor.material.color = Color{1, 0.9, 0.9};
    floor.material.specular = 0;
    world.objects.push_back(floor);

    Sphere left_wall{};
    left_wall.transform = translation(0, 0, 5) * rotate_y(-(M_PI / 4)) * rotate_x(M_PI / 2) * scaling(10, 0.01, 10);
    left_wall.material = floor.material;
    world.objects.push_back(left_wall);

    Sphere right_wall{};
    right_wall.transform = translation(0, 0, 5) * rotate_y(M_PI / 4) * rotate_x(M_PI / 2) * scaling(10, 0.01, 10);
    right_wall.material = floor.material;
    world.objects.push_back(right_wall);

    Sphere middle{};
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material.color = Color{0.1, 1, 0.5};
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    world.objects.push_back(middle);

    Sphere right{};
    right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
    right.material.color = Color{0.5, 1, 0.1};
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    world.objects.push_back(right);

    Sphere left{};
    left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
    left.material.color = Color{1, 0.8, 0.1};
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    world.objects.push_back(left);

    world.lights.push_back(PointLight{point(-10, 10, -10), Color{1, 1, 1}});
    Camera cam{100, 50, M_PI / 3};
    cam.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));

    world.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");
}

} // namespace TESTS
