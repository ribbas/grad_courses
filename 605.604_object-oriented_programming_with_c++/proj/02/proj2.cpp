#include "customer.hpp"
#include "rng.hpp"

#include <deque>
#include <iostream>
#include <vector>

const double MINUTES_PER_HOUR = 60.0;

class Simulation {
public:
    Simulation()
        : arrival_times_rng(30.0), check_in_times_rng(1.0, 4.0),
          vaccination_times_rng(15.0) {
        num_customers_ = 100;
    }

    ~Simulation() {
        for (auto i : new_arrivals_array_) {
            delete i;
        }
    }

    void assign_phase_times() {

        for (int i = 0; i < num_customers_; i++) {

            auto c = new Customer();

            c->set_arrival_time(arrival_times_rng.get() * MINUTES_PER_HOUR);
            c->set_check_in_time(check_in_times_rng.get());
            c->set_vaccination_time(vaccination_times_rng.get() *
                                    MINUTES_PER_HOUR);

            new_arrivals_array_.push_back(c);
        }
    }

    void assign_seniors() {

        int percentage_seniors = num_customers_ * 0.60;
        for (auto c : new_arrivals_array_) {

            if (percentage_seniors) {
                c->make_senior();
                percentage_seniors--;
            }
        }

        shuffle(new_arrivals_array_.begin(), new_arrivals_array_.end());
    }

    void queue_new_arrivals() {

        int tick = 0;
        double total_arrival_time = 0;

        std::vector<Customer*> waiting_line;

        while (tick < MINUTES_PER_HOUR && !new_arrivals_array_.empty()) {

            if (total_arrival_time < tick) {
                total_arrival_time +=
                    new_arrivals_array_.front()->get_arrival_time();
                auto c = new_arrivals_array_.front();
                new_arrivals_array_.pop_front();
                waiting_line.push_back(c);
                // std::cout << tick << '\n';
                std::cout << tick << ' ' << c->is_senior() << ' '
                          << c->get_arrival_time() << ' '
                          << c->get_check_in_time() << ' '
                          << c->get_vaccination_time() << ' '
                          << total_arrival_time << '\n';
            } else {
                std::cout << "Next\n";
                send_to_station(waiting_line);
                waiting_line.clear();
                // std::vector<Customer*> waiting_line;
                // auto waiting_line = new std::vector<Customer*>;
                tick++;
            }
        }
    }

    void send_to_station(std::vector<Customer*> waiting_line) {
        // for (auto c : waiting_line) {
        //     std::cout << c->is_senior() << ' ' << c->get_arrival_time() << '
        //     '
        //               << c->get_check_in_time() << ' '
        //               << c->get_vaccination_time() << '\n';
        // }
    }

    void generate_num_customers() {
        num_customers_ = 100;
    }

private:
    ExponentialDistribution arrival_times_rng;
    UniformDistribution check_in_times_rng;
    ExponentialDistribution vaccination_times_rng;

    std::deque<Customer*> new_arrivals_array_;

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
    sim.assign_phase_times();
    sim.assign_seniors();
    sim.queue_new_arrivals();

    return 0;
}
