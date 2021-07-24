/*
 * customer.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the function declarations for the Customer class.
 *
 */

#ifndef RNG_HPP
#define RNG_HPP

#include <random>

template <class T>
class RNG {

public:
    RNG() {}

    ~RNG() {}

    void reseed(int seed) {
        distribution_.reset();
        srand(seed);
    }

    double get() {
        return distribution_(generator_);
    }

protected:
    T distribution_;
    double random_num_;

private:
    std::default_random_engine generator_;
};

class ExponentialDistribution
    : public RNG<std::exponential_distribution<double>> {
public:
    ExponentialDistribution(double upper_bound, int seed = 0) {

        srand(seed);

        this->random_num_ = 0.0;

        typename std::exponential_distribution<double>::param_type new_lambda(
            upper_bound);
        this->distribution_.param(new_lambda);
    }
};

class UniformDistribution : public RNG<std::uniform_real_distribution<double>> {
public:
    UniformDistribution(double lower_bound, double upper_bound, int seed = 0) {

        srand(seed);

        this->random_num_ = 0.0;

        typename std::uniform_real_distribution<double>::param_type new_lambda(
            lower_bound, upper_bound);
        this->distribution_.param(new_lambda);
    }
};

#endif
