#include "rng.hpp"
#include <iostream>

int main() {
    auto rng = new ExponentialDistribution(30.0);
    std::cout << rng->get() << '\n';
    std::cout << rng->get() << '\n';
    std::cout << rng->get() << '\n';
    std::cout << rng->get() << '\n';
    std::cout << rng->get() << '\n';

    auto rng1 = new UniformDistribution(1.0, 3.0);
    std::cout << rng1->get() << '\n';

    delete rng;
    delete rng1;

    return 0;
}
