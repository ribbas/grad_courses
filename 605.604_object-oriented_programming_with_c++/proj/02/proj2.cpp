#include "customer.hpp"
#include "rng.hpp"
#include "station.hpp"

#include <deque>
#include <iostream>
#include <vector>

const double MINUTES_PER_HOUR = 60.0;

class Simulation {
public:
    Simulation()
        : arrival_times_rng(30.0), check_in_times_rng(1.0, 4.0),
          vaccination_times_rng(15.0) {
        num_customers_ = 10;
    }

    ~Simulation() {
        for (auto i : new_arrivals_array_) {
            delete i;
        }
    }

    void assign_phase_times() {

        double total_arrival_time = arrival_times_rng.get();
        for (auto c : new_arrivals_array_) {

            c->set_arrival_time(total_arrival_time * MINUTES_PER_HOUR);
            c->set_check_in_time(check_in_times_rng.get());
            c->set_vaccination_time(vaccination_times_rng.get() *
                                    MINUTES_PER_HOUR);
            total_arrival_time += arrival_times_rng.get();
        }
    }

    void assign_seniors() {

        int percentage_seniors = num_customers_ * 0.60;
        for (int i = 0; i < num_customers_; i++) {

            auto c = new Customer();

            if (percentage_seniors) {
                c->make_senior();
                percentage_seniors--;
            }
            new_arrivals_array_.push_back(c);
        }

        shuffle(new_arrivals_array_.begin(), new_arrivals_array_.end());
    }

    void queue_new_arrivals() {

        int tick = 0;
        double total_time = new_arrivals_array_.front()->get_wait_time();

        while (tick < MINUTES_PER_HOUR && !new_arrivals_array_.empty()) {

            std::cout << new_arrivals_array_.front() << " arr: "
                      << new_arrivals_array_.front()->get_arrival_time()
                      << " chk: "
                      << new_arrivals_array_.front()->get_check_in_time()
                      << " vax: "
                      << new_arrivals_array_.front()->get_vaccination_time()
                      << " tot: "
                      << new_arrivals_array_.front()->get_wait_time() << '\n';
            std::cout << "current time: " << total_time << '\n';

            // send_to_station(tick, total_time);
            // station.send_home(tick, total_time);

            if (total_time <= tick && new_arrivals_array_.size()) {
                std::cout << "vaxxing " << new_arrivals_array_.front() << ' '
                          << new_arrivals_array_.size() << "\n\n\n";
                new_arrivals_array_.pop_front();
                if (!new_arrivals_array_.empty()) {
                    total_time = new_arrivals_array_.front()->get_wait_time();
                }
            } else {
                tick++;
                std::cout << "ticking " << tick << '\n';
            }
        }
    }

    void send_to_station(int tick, double total_time) {
        // auto c = new_arrivals_array_.front();
        if (station.vaccinate(new_arrivals_array_.front(), tick, total_time)) {
            std::cout << new_arrivals_array_.front() << " sent\n";
            new_arrivals_array_.pop_front();
        }
    }

    void generate_num_customers() {
        num_customers_ = 10;
    }

private:
    ExponentialDistribution arrival_times_rng;
    UniformDistribution check_in_times_rng;
    ExponentialDistribution vaccination_times_rng;

    std::deque<Customer*> new_arrivals_array_;

    VaccinationStation station;

    int num_customers_;

    void shuffle(std::deque<Customer*>::iterator first,
                 std::deque<Customer*>::iterator last) {
        auto g = std::default_random_engine(0);
        for (auto i = (last - first) - 1; i > 0; --i) {
            std::uniform_int_distribution<int> d(0, i);
            std::swap(first[i], first[d(g)]);
        }
    }
};

int main() {

    Simulation sim;
    sim.assign_seniors();
    sim.assign_phase_times();
    sim.queue_new_arrivals();

    return 0;
}
