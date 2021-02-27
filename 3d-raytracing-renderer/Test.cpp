#include "TestFunctions.h"

int main()
{

    World w = DEFAULT_WORLD();
    w.objects[0].material.ambient = 1;
    w.objects[1].material.ambient = 1;

    Ray r{point(0, 0, 0.75), vector(0, 0, -1)};
    Color clr = color_at(w, r);
    TESTS::printColor(w.objects[1].material.color);
    TESTS::printColor(clr);

    /*World w{};

    Sphere sp{};
    sp.material.color = Color{0.8, 1, 0.6};
    w.objects.push_back(sp);

    Sphere sp__{};
    sp__.material.color = Color{0.3, 0.7, 0.9};
    sp__.transform = translation(-0.3, 0, -1.7) * scaling(0.3, 0.3, 0.3);
    w.objects.push_back(sp__);

    PointLight light{point(-10, 10, -10), Color{1, 1, 1}};
    w.lights.push_back(light);

    Camera cam{300, 150, M_PI / 3};
    cam.transform = view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));
    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene2.ppm");*/

    // TESTS::CanvasTest();

    system("pause");
    return 0;
}
