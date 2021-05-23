#include "TestFunctions.h"

int main()
{

    World w{};

    Sphere sp{};
    sp.material.reflective = 1;
    sp.material.specular = 0.9;
    sp.material.diffuse = 0.7;
    sp.material.ambient = 0.6;
    sp.setTransform(translation(0, 1, 0));
    w.addShape<Sphere>(sp);

    Plane underground{};
    w.addShape<Plane>(underground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{400, 200, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 1, -5), point(0, 1, 0), vector(0, 1, 0)));
    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    /*World w = DEFAULT_WORLD();

    Plane obj{};
    obj.material.reflective = 0.5;
    obj.setTransform(translation(0, -1, 0));
    w.addShape<Plane>(obj);

    Ray r{point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2)};
    Intersection i{sqrt(2), &obj};
    Computations comps = prepare_computations(i, r);

    Color clr = shade_hit(w, comps, 4);
    TESTS::printColor(clr);*/

    system("pause");
    return 0;
}
