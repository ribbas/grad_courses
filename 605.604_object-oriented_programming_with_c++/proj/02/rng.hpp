/*
 * rng.hpp
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

template <class T> class RNG {

public:
    RNG(int = 0);

    ~RNG() {}

    void reseed(int);

    double get();

protected:
    T distribution_;
    double random_num_;

private:
    std::default_random_engine generator_;
};

class ExponentialDistribution
    : public RNG<std::exponential_distribution<double>> {
public:
    ExponentialDistribution(double, int = 0);
};

class UniformDistribution : public RNG<std::uniform_real_distribution<double>> {
public:
    UniformDistribution(double, double, int = 0);
};

#endif
