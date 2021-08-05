#include "simulation.hpp"

Simulation::Simulation()
    : arrival_times_rng_(30.0), check_in_times_rng_(1.0, 4.0),
      vaccination_times_rng_(15.0), days_(1) {
    num_customers_ = 1000;
}

Simulation::~Simulation() {
    for (auto i : new_arrivals_array_) {
        delete i;
        i = nullptr;
    }
}

void Simulation::simulate_days(int num_days) {

    for (int i = 0; i < num_days; i++) {

        assign_seniors();
        assign_phase_times();
        queue_new_arrivals();
    }
}

void Simulation::assign_phase_times() {

    double total_arrival_time = arrival_times_rng_.get();
    for (auto c : new_arrivals_array_) {

        c->set_arrival_time(total_arrival_time * MINUTES_PER_HOUR);
        c->set_check_in_time(check_in_times_rng_.get());
        c->set_vaccination_time(vaccination_times_rng_.get() *
                                MINUTES_PER_HOUR);
        total_arrival_time += arrival_times_rng_.get();
    }
}

void Simulation::assign_seniors() {

    int percentage_seniors = num_customers_ * SENIOR_PERCENTAGE;
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

void Simulation::queue_new_arrivals() {

    int tick = 0;
    std::sort(new_arrivals_array_.begin(), new_arrivals_array_.end(),
              customer_comparator);
    double wait_time = new_arrivals_array_.front()->get_wait_time();

    while (tick < MINUTES_PER_HOUR * HOURS_OF_OPERATION &&
           !new_arrivals_array_.empty()) {

        std::cout << new_arrivals_array_.front()
                  << " arr: " << new_arrivals_array_.front()->get_arrival_time()
                  << " chk: "
                  << new_arrivals_array_.front()->get_check_in_time()
                  << " vax: "
                  << new_arrivals_array_.front()->get_vaccination_time()
                  << " wait: " << new_arrivals_array_.front()->get_wait_time()
                  << " tot: " << new_arrivals_array_.front()->get_total_time()
                  << '\n';

        station_.send_home(tick);

        if (wait_time <= tick && new_arrivals_array_.size() &&
            add_to_line(tick)) {

            // if there are still customers left, keep looping
            if (!new_arrivals_array_.empty()) {
                wait_time = new_arrivals_array_.front()->get_wait_time();
            }

        } else {
            tick++;
            std::cout << "ticking " << tick << '\n';
        }
    }
}

bool Simulation::add_to_line(int tick) {

    if (station_.find_available_station() != -1) {

        std::cout << "vaxxing " << new_arrivals_array_.front() << " at " << tick
                  << "\n\n\n";
        station_.vaccinate(new_arrivals_array_.front());
        new_arrivals_array_.pop_front();

        return true;

    } else {

        std::cout << "can't vax " << new_arrivals_array_.front() << " yet\n";

        return false;
    }
}

void Simulation::generate_num_customers() {
    num_customers_ = 10;
}

bool Simulation::customer_comparator(Customer* c1, Customer* c2) {

    if (std::floor(c1->get_wait_time()) == std::floor(c2->get_wait_time())) {

        return c1->is_senior() > c2->is_senior();

    } else {

        return c1->get_wait_time() < c2->get_wait_time();
    }
}

void Simulation::shuffle(std::deque<Customer*>::iterator first,
                         std::deque<Customer*>::iterator last) {
    auto g = std::default_random_engine(0);
    for (auto i = (last - first) - 1; i > 0; --i) {
        std::uniform_int_distribution<int> d(0, i);
        std::swap(first[i], first[d(g)]);
    }
}
