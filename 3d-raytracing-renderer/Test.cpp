#include "TestFunctions.h"


int main()
{

    /*Ray r{point(0, 0, -5), vector(0, 0, 1)};
    Sphere sp{};
    sp.transform = translation(0, 0, 1);
    Intersection i{5, sp};

    std::cout << -EPSILON / 2 << std::endl;
    Computations comps = prepare_computations(i, r);
    TESTS::printComputations(comps)*/;

    TESTS::CanvasTest();

    system("pause");
    return 0;
}
