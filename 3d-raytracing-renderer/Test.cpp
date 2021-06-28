#include "TestFunctions.h"

int main()
{

    World w{};

    Sphere sp{};
    sp.material.pattern = new JitteredPattern{
        std::make_shared<StripePattern>(StripePattern{highvalueColor(62, 107, 98), highvalueColor(178, 192, 161)}),
        0.6};
    sp.material.pattern->setTransform(rotate_z(toRadians(50)) * scaling(0.4, 0.4, 0.4));
    sp.material.specular = 0.9;
    sp.material.diffuse = 0.7;
    sp.material.ambient = 0.6;
    sp.setTransform(translation(0, 1, 0));
    w.objects.push_back(&sp);

    Plane underground{};

    auto sOne = JitteredPattern{
        std::make_shared<StripePattern>(StripePattern{highvalueColor(158, 201, 212), highvalueColor(66, 91, 123)}),
        0.6};
    auto sTwo = StripePattern{highvalueColor(66, 91, 123), highvalueColor(158, 201, 212)};
    sTwo.setTransform(rotate_y(toRadians(90)) * scaling(0.7, 0.7, 0.7));
    sOne.setTransform(scaling(0.7, 0.7, 0.7));

    underground.material.pattern = new BlendPattern{&sOne, &sTwo};
    w.objects.push_back(&underground);

    w.light = PointLight{point(-10, 10, -5), Color{1, 1, 1}};

    Camera cam{400, 200, M_PI / 3};
    cam.setTransformation(view_transform(point(0, 1, -5), point(0, 1, 0), vector(0, 1, 0)));

    w.render(cam).toPPM("C:\\Users\\tompe\\desktop\\scene.ppm");

    system("pause");
    return 0;
}
