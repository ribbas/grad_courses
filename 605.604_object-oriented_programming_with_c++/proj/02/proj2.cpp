#include "customer.hpp"
#include "rng.hpp"

#include <iostream>

int main() {

    auto rng = new ExponentialDistribution(30.0, 123);

    double arrivalTime = 0;
    int num_customers = 0;

    while (arrivalTime <= 60.0) {

        num_customers++;

        double v = rng->get() * 60.0;
        arrivalTime += v;
        if (arrivalTime <= 60.0) {

            std::cout << "InterArrival Time = " << v
                      << "\tArrivalTime = " << arrivalTime << std::endl;
        }
    }

    std::cout << num_customers << '\n';

    delete rng;

    auto c = new Customer();

    c->progress();
    c->progress();
    c->progress();
    c->progress();
    c->progress();
    c->progress();
    c->progress();
    c->progress();

    std::cout << c->get_state() << '\n';

    return 0;
}
