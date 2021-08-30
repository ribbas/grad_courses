/*
 * rng.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the function declarations for the RNG base class and its
 * derived subclasses, ExponentialDistribution and UniformDistribution.
 *
 */

#ifndef RNG_HPP
#define RNG_HPP

#include <random>

template <class T>
class RNG {

public:
    /* ---------- PUBLIC METHODS ---------- */
    void reseed(int);

    double get();

protected:
    /* ---------- CONSTRUCTORS ---------- */
    RNG(int = 0);

    T distribution_;
    double random_num_;

private:
    std::default_random_engine generator_;
};

class ExponentialDistribution
    : public RNG<std::exponential_distribution<double>> {
public:
    /* ---------- CONSTRUCTORS ---------- */
    ExponentialDistribution(double, int = 0);
};

class UniformDistribution : public RNG<std::uniform_real_distribution<double>> {
public:
    /* ---------- CONSTRUCTORS ---------- */
    UniformDistribution(double, double, int = 0);
};

#endif
