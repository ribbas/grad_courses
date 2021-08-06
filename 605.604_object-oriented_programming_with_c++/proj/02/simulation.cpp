#include "simulation.hpp"

Simulation::Simulation(int num_days)
    : arrival_times_rng_(30.0), check_in_times_rng_(1.0, 4.0),
      vaccination_times_rng_(15.0), num_customers_(500), num_days_(num_days),
      total_customers_served_(0), ave_check_in_time_(0.0),
      ave_vaccination_time_(0.0) {}

Simulation::~Simulation() {
    for (auto i : new_arrivals_array_) {
        delete i;
        i = nullptr;
    }
}

void Simulation::simulate_days() {

    for (int i = 0; i < num_days_; i++) {

        assign_seniors();
        shuffle(new_arrivals_array_.begin(), new_arrivals_array_.end());
        assign_phase_times();
        std::sort(new_arrivals_array_.begin(), new_arrivals_array_.end(),
                  customer_comparator);
        queue_new_arrivals();

        station_.reset();
    }
}

void Simulation::get_statistics() {
    std::cout << "CUSTOMERS SERVED TOTAL "
              << (total_customers_served_ / num_days_) << '\n';
    std::cout << "AVERAGE QUEUE TIME "
              << (ave_check_in_time_ / total_customers_served_) << " MINUTES\n";
    std::cout << "AVERAGE VACCINATION TIME "
              << (ave_vaccination_time_ / total_customers_served_)
              << " MINUTES\n";
    std::cout << "AVERAGE TOTAL TIME "
              << ((ave_check_in_time_ + ave_vaccination_time_) /
                  total_customers_served_)
              << " MINUTES\n";
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

void Simulation::queue_new_arrivals() {

    int tick = 0;
    double wait_time = new_arrivals_array_.front()->get_wait_time();

    while (tick < MINUTES_PER_HOUR * HOURS_OF_OPERATION &&
           !new_arrivals_array_.empty()) {

        station_.poll(tick);

        if (wait_time <= tick && new_arrivals_array_.size() && add_to_line()) {

            // if there are still customers left, keep looping
            if (!new_arrivals_array_.empty()) {
                wait_time = new_arrivals_array_.front()->get_wait_time();
            }

        } else {
            tick++;
        }
    }
}

bool Simulation::add_to_line() {

    int available_station_num = station_.find_available_station();

    if (available_station_num != -1) {

        station_.vaccinate(new_arrivals_array_.front(), available_station_num);
        total_customers_served_++;
        ave_check_in_time_ += new_arrivals_array_.front()->get_check_in_time();
        ave_vaccination_time_ +=
            new_arrivals_array_.front()->get_vaccination_time();

        new_arrivals_array_.pop_front();

        return true;

    } else {

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
