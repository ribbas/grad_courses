#include "customer.hpp"
#include "rng.hpp"

#include <iostream>
#include <vector>

void shuffle(std::vector<Customer*>::iterator first,
             std::vector<Customer*>::iterator last) {
    auto g = std::default_random_engine(0);
    for (auto i = (last - first) - 1; i > 0; --i) {
        std::uniform_int_distribution<int> d(0, i);
        std::swap(first[i], first[d(g)]);
    }
}

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
                      << "\tArrivalTime = " << arrivalTime << '\n';
        }
    }

    std::vector<Customer*> new_arrivals_array;
    int percentage_seniors = num_customers * 0.60;

    for (int i = 0; i < num_customers; i++) {
        auto c = new Customer();
        new_arrivals_array.push_back(c);
        if (percentage_seniors) {
            c->make_senior();
            percentage_seniors--;
        }
        c->progress();
    }

    shuffle(new_arrivals_array.begin(), new_arrivals_array.end());

    for (auto i : new_arrivals_array) {
        std::cout << i->is_senior() << '\n';
    }

    delete rng;

    return 0;
}
