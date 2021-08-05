#include "customer.hpp"
#include "rng.hpp"
#include "station.hpp"

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

const double MINUTES_PER_HOUR = 60.0;

class Simulation {
public:
    Simulation()
        : arrival_times_rng(30.0), check_in_times_rng(1.0, 4.0),
          vaccination_times_rng(15.0) {
        num_customers_ = 40;
    }

    ~Simulation() {
        for (auto i : new_arrivals_array_) {
            delete i;
            i = nullptr;
        }

        std::cout << "deleting waiting line\n";
        for (auto j : waiting_line_) {
            std::cout << j << '\n';
            delete j;
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
        // std::sort(new_arrivals_array_.begin(), new_arrivals_array_.end(),
        //           compare_customers);
        double wait_time = new_arrivals_array_.front()->get_wait_time();

        while (tick < MINUTES_PER_HOUR && !new_arrivals_array_.empty()) {

            std::cout << new_arrivals_array_.front() << " arr: "
                      << new_arrivals_array_.front()->get_arrival_time()
                      << " chk: "
                      << new_arrivals_array_.front()->get_check_in_time()
                      << " vax: "
                      << new_arrivals_array_.front()->get_vaccination_time()
                      << " wait: "
                      << new_arrivals_array_.front()->get_wait_time()
                      << " tot: "
                      << new_arrivals_array_.front()->get_total_time() << '\n';

            station.send_home(tick);

            if (wait_time <= tick && new_arrivals_array_.size()) {

                if (add_to_line(tick)) {

                    // if there are still customers left, keep looping
                    if (!new_arrivals_array_.empty()) {
                        wait_time =
                            new_arrivals_array_.front()->get_wait_time();
                    }
                } else {
                    tick++;
                }

            } else {
                tick++;
                std::cout << "ticking " << tick << '\n';
            }
        }
    }

    bool send_to_station(int tick) {

        Customer* first = waiting_line_.front();
        Customer* last = waiting_line_.begin()[1];
        if (!first->is_senior() && last->is_senior()) {
            std::cout << "in line found front" << last << " at " << tick
                      << " with " << last->is_senior() << '\n';
            station.vaccinate(last);
            waiting_line_.pop_back();
        } else {
            std::cout << "in line found last" << first << " at " << tick
                      << " with " << first->is_senior() << '\n';
            station.vaccinate(first);
            waiting_line_.pop_front();
        }

        return true;
    }

    bool add_to_line(int tick) {

        if (station.find_available_station() != -1) {

            if (waiting_line_.size() > 1) {
                send_to_station(tick);
                // std::cout << "vaxxing from line" << waiting_line_.back()
                //           << " at " << tick << "\n\n\n";
                // station.vaccinate(waiting_line_.back());
                // waiting_line_.pop_back();
                // } else {
                // station.vaccinate(new_arrivals_array_.front());
            } else {

                std::cout << "vaxxing " << new_arrivals_array_.front() << " at "
                          << tick << "\n\n\n";
                station.vaccinate(new_arrivals_array_.front());

                new_arrivals_array_.pop_front();
            }
            return true;

        } else {

            waiting_line_.insert(
                waiting_line_.end(),
                std::make_move_iterator(new_arrivals_array_.begin()),
                std::make_move_iterator(new_arrivals_array_.begin() + 1));
            // std::cout << "moved\n";
            std::cout << "can't vax " << new_arrivals_array_.front()
                      << " yet\n";
            new_arrivals_array_.pop_front();

            return false;
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

    std::deque<Customer*> waiting_line_;

    VaccinationStation station;

    int num_customers_;

    static bool compare_customers(Customer* c1, Customer* c2) {
        return c1->get_wait_time() < c2->get_wait_time();
    }

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
