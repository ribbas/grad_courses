#include "customer.hpp"
#include "rng.hpp"

#include <deque>
#include <iostream>
#include <vector>

class Simulation {
public:
    ~Simulation() {
        for (auto i : new_arrivals_array_) {
            delete i;
        }
    }

    void generate_new_arrivals(std::deque<double>* arrival_times) {

        int num_customers = arrival_times->size();
        int percentage_seniors = num_customers * 0.60;

        auto check_in_times_rng = new UniformDistribution(1.0, 4.0);
        auto vaccination_times_rng = new ExponentialDistribution(15.0);

        for (int i = 0; i < num_customers; i++) {
            auto c = new Customer();
            c->set_arrival_time((*arrival_times)[i]);
            c->set_check_in_time(check_in_times_rng->get());
            c->set_vaccination_time(vaccination_times_rng->get() * 60.0);
            new_arrivals_array_.push_back(c);
            if (percentage_seniors) {
                c->make_senior();
                percentage_seniors--;
            }
            c->progress();
        }

        shuffle(new_arrivals_array_.begin(), new_arrivals_array_.end());
    }

    void queue_new_arrivals() {

        int tick = 0;
        double total_arrival_time = 0;

        std::vector<Customer*> waiting_line;

        while (tick < MINUTES_PER_HOUR_ && !new_arrivals_array_.empty()) {

            if (total_arrival_time < tick) {
                total_arrival_time +=
                    new_arrivals_array_.front()->get_arrival_time();
                auto c = new_arrivals_array_.front();
                new_arrivals_array_.pop_front();
                waiting_line.push_back(c);
                // std::cout << tick << ' ' << c->is_senior() << ' '
                //           << c->get_arrival_time() << ' '
                //           << c->get_check_in_time() << '\n';
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
        for (auto c : waiting_line) {
            std::cout << c->is_senior() << ' ' << c->get_arrival_time() << ' '
                      << c->get_check_in_time() << ' '
                      << c->get_vaccination_time() << '\n';
        }
    }

private:
    const int MINUTES_PER_HOUR_ = 60;
    std::deque<Customer*> new_arrivals_array_;

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

    auto arrival_times_rng = new ExponentialDistribution(30.0);

    double total_arrival_time = 0;
    auto arrival_times = new std::deque<double>;

    while (total_arrival_time <= 60.0) {

        double v = arrival_times_rng->get() * 60.0;
        arrival_times->push_back(v);
        total_arrival_time += v;
        if (total_arrival_time <= 60.0) {

            std::cout << "InterArrival Time = " << v
                      << "\tArrivalTime = " << total_arrival_time << '\n';
        }
    }

    auto sim = new Simulation();
    sim->generate_new_arrivals(arrival_times);
    sim->queue_new_arrivals();

    delete arrival_times_rng;
    delete sim;

    return 0;
}
