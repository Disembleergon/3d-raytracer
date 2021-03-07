#include "TestFunctions.h"

int main()
{

    /*Sphere s{};
    s.transform = translation(0, 1, 0);
    auto n = s.normal_at(point(0, 1.70711, -0.70711));
    TESTS::printTuple(n);*/

    /*Sphere s{};
    s.transform = scaling(1, 0.5, 1) * rotate_z(M_PI / 5);
    Tuple n = s.normal_at(point(0, sqrt(2)/2, -sqrt(2)/2));
    TESTS::printTuple(n);*/

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

    Camera cam{100, 50, M_PI / 3};
    cam.transform = view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));
    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene2.ppm");*/

    TESTS::CanvasTest();

    system("pause");
    return 0;
}
