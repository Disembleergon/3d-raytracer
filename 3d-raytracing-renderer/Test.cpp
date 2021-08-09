#include "TestFunctions.h"

int main()
{
    /*World w = DEFAULT_WORLD();

    Plane floor{};
    floor.setTransform(translation(0, -1, 0));
    floor.material.transparency = 0.5;
    floor.material.refractive_index = 1.5;
    w.addShape<Plane>(floor);

    Sphere ball{};
    ball.material.color = Color{1, 0, 0};
    ball.material.ambient = 0.5;
    ball.setTransform(translation(0, -3.5, -0.5));
    w.addShape<Sphere>(ball);

    Ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    IntersectionList xs = {Intersection{sqrt(2), &floor }};

    auto comps = prepare_computations(xs[0], r, xs);
    Color clr = shade_hit(w, comps, 5);
    TESTS::printColor(clr);*/

    World w{};

    Plane wall{};
    wall.setTransform(rotate_x(1.5708) * translation(0, 0, 10));

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

    w.light = PointLight{point(2, 10, -5), Color{0.9, 0.9, 0.9}};

    Camera cam{300, 300, .5};
    cam.setTransformation(view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    return 0;
}
