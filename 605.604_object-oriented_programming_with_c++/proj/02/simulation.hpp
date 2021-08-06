#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "customer.hpp"
#include "rng.hpp"
#include "station.hpp"
#include <algorithm>
#include <deque>
#include <iostream>

const double MINUTES_PER_HOUR = 60.0;
const int HOURS_OF_OPERATION = 12;
const float SENIOR_PERCENTAGE = 0.60;

class Simulation {
public:
    Simulation();

    ~Simulation();

    void assign_phase_times();

    void assign_seniors();

    void queue_new_arrivals();

    void simulate_days(int);

private:
    ExponentialDistribution arrival_times_rng_;
    UniformDistribution check_in_times_rng_;
    ExponentialDistribution vaccination_times_rng_;

    std::deque<Customer*> new_arrivals_array_;

    VaccinationStation station_;

    int num_customers_;

    int days_;

    int total_customers_served_;

    void generate_num_customers();

    bool add_to_line();

    static bool customer_comparator(Customer*, Customer*);

    void shuffle(std::deque<Customer*>::iterator,
                 std::deque<Customer*>::iterator);
};

#endif