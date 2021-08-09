#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "customer.hpp"
#include "rng.hpp"
#include "station.hpp"

#include <algorithm>
#include <deque>
#include <iostream>

const unsigned int MINUTES_PER_HOUR = 60;
const unsigned int HOURS_OF_OPERATION = 12;
const unsigned int MAX_CUSTOMERS = 500;
const float SENIOR_PERCENTAGE = 0.60;

class Simulation {
public:
    Simulation(int);

    ~Simulation();

    void simulate_days();

    void get_statistics();

private:
    void assign_phase_times();

    void assign_seniors();

    void simulate_queue();

    void generate_num_customers();

    bool add_to_line(int);

    void sort_customers();

    void shuffle_customers();

    ExponentialDistribution arrival_times_rng_;
    UniformDistribution check_in_times_rng_;
    ExponentialDistribution vaccination_times_rng_;
    std::deque<Customer*> customers_;
    VaccinationStation station_;

    int num_days_;
    int total_customers_served_, customers_served_today_;
    double ave_check_queue_time_, ave_vax_queue_time_, ave_total_time_,
        check_queue_time_today_, vax_queue_time_today_, total_time_today_;
};

#endif
