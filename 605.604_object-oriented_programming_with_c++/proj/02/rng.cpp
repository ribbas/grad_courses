/*
 * rng.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the implementation of the RNG base class and its
 * derived subclasses, ExponentialDistribution and UniformDistribution.
 *
 */
#include "rng.hpp"

#include <iostream>

// explicit template instantiation of the RNG subclasses
template class RNG<std::exponential_distribution<double>>;
template class RNG<std::uniform_real_distribution<double>>;

/*
 * Default parameterized constructor
 *
 * Params:
 *  seed <int>: seed number
 *
 * Returns:
 *  None
 */
template <class T>
RNG<T>::RNG(int seed) : generator_(seed) {}

/*
 * Reseed the random engine
 *
 * Params:
 *  seed <int>: seed number
 *
 * Returns:
 *  None
 */
template <class T>
void RNG<T>::reseed(int seed) {
    generator_.seed(seed);
}

/*
 * Get the random number yielded from the generator
 *
 * Params:
 *  None
 *
 * Returns:
 *  <double>: generated random double
 */

template <class T>
double RNG<T>::get() {
    return distribution_(generator_);
}

/*
 * Default parameterized constructor
 *
 * Params:
 *  lambda <double>: lambda of the distribution
 *  seed <int>: seed number
 *
 * Returns:
 *  None
 */
ExponentialDistribution::ExponentialDistribution(double lambda, int seed)
    : RNG(seed) {

    // initialize the base class variable
    this->random_num_ = 0.0;

    // initialize the base class generator with the user defined parameters
    typename std::exponential_distribution<double>::param_type params(lambda);
    this->distribution_.param(params);
}

/*
 * Default parameterized constructor
 *
 * Params:
 *  a <double>: lower bound of the range the distribution
 *  b <double>: upper bound of the range the distribution
 *  seed <int>: seed number
 *
 * Returns:
 *  None
 */
UniformDistribution::UniformDistribution(double a, double b, int seed)
    : RNG(seed) {

    // initialize the base class variable
    this->random_num_ = 0.0;

    // initialize the base class generator with the user defined parameters
    typename std::uniform_real_distribution<double>::param_type params(a, b);
    this->distribution_.param(params);
}
