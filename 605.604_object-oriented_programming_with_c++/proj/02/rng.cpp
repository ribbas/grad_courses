#include "rng.hpp"

#include <iostream>

template class RNG<std::exponential_distribution<double>>;
template class RNG<std::uniform_real_distribution<double>>;

template <class T>
RNG<T>::RNG(int seed) : generator_(seed) {}

template <class T>
void RNG<T>::reseed(int seed) {
    generator_.seed(seed);
}

template <class T>
double RNG<T>::get() {
    return distribution_(generator_);
}

ExponentialDistribution::ExponentialDistribution(double upper_bound, int seed)
    : RNG(seed) {

    this->random_num_ = 0.0;

    typename std::exponential_distribution<double>::param_type params(
        upper_bound);
    this->distribution_.param(params);
}

UniformDistribution::UniformDistribution(double lower_bound, double upper_bound,
                                         int seed)
    : RNG(seed) {

    this->random_num_ = 0.0;

    typename std::uniform_real_distribution<double>::param_type params(
        lower_bound, upper_bound);
    this->distribution_.param(params);
}

double get_random_number_with_minimum_mean_and_maximum(double minimum,
                                                       double mean,
                                                       double maximum) {

    // Any uniform random generator of your choice could be used here.
    // Obviously making this static is not rentrant or thread-safe.
    static std::mt19937 generator;

    // We'll start with a normal distribution with a standard deviation set
    // such that ~99.7% of the time we'll get a number within the average width
    // of your upper and lower bounds.
    //
    // Why ~99.7% and not some other number? Because that corresponds to three
    // standard deviations, and you didn't specify any requirements, so I'm
    // just making assumptions on your behalf.
    double const average_bound_width =
        ((mean - minimum) + (maximum - mean)) / 2;
    double const standard_deviation = average_bound_width / 3;
    std::normal_distribution<double> distribution(mean, standard_deviation);

    // Now, keep fetching numbers until we find one that is within our desired
    // bounds. Throwing numbers away randomly from a normal distribution does
    // not affect the mean, but since our bounds are going to be skewed, our
    // mean will probably get skewed slightly, but this will likely not be
    // very noticable.
    double value;
    do {
        value = distribution(generator);
    } while (value < minimum || maximum < value);

    return value;
}
