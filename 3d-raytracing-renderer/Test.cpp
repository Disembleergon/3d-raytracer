#include "TestFunctions.h"

int main()
{

    /*World w{};

    Sphere sp{};
    sp.material.reflective = 0.5;
    sp.material.specular = 0.9;
    sp.material.diffuse = 0.7;
    sp.material.ambient = 0.6;
    sp.setTransform(translation(0, 1, 0));
    w.addShape<Sphere>(sp);

    Plane underground{};
    w.addShape<Plane>(underground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{100, 50, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 1, -5), point(0, 1, 0), vector(0, 1, 0)));
    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");*/


    TESTS::CanvasTest();

    system("pause");
    return 0;
}
