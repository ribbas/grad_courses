#include "simulation.hpp"

Simulation::Simulation(int num_days)
    : arrival_times_rng_(30.0), check_in_times_rng_(1.0, 4.0),
      vaccination_times_rng_(15.0), num_days_(num_days),
      total_customers_served_(0), customers_served_today_(0),
      ave_check_queue_time_(0.0), ave_vax_queue_time_(0.0),
      ave_total_time_(0.0), check_queue_time_today_(0.0),
      vax_queue_time_today_(0.0), total_time_today_(0.0) {}

Simulation::~Simulation() {
    for (auto i : customers_) {
        delete i;
        i = nullptr;
    }
}

void Simulation::simulate_days() {

    for (int i = 0; i < num_days_; i++) {

        assign_seniors();
        shuffle_customers();

        assign_phase_times();
        sort_customers();

        simulate_queue();

        std::cout << "DAY " << (i + 1) << " STATISTICS:\n";
        std::cout << "----------------------------------------\n";
        std::cout << "CUSTOMERS SERVED: " << customers_served_today_ << '\n';
        std::cout << "AVERAGE CHECK-IN QUEUE TIME: "
                  << (check_queue_time_today_ / customers_served_today_)
                  << " MINUTES\n";
        std::cout << "AVERAGE VACCINATION QUEUE TIME: "
                  << (vax_queue_time_today_ / customers_served_today_)
                  << " MINUTES\n";
        std::cout << "AVERAGE TOTAL TIME: "
                  << (total_time_today_ / customers_served_today_)
                  << " MINUTES\n\n\n";

        ave_check_queue_time_ += check_queue_time_today_;
        ave_vax_queue_time_ += vax_queue_time_today_;
        ave_total_time_ += total_time_today_;
        total_customers_served_ += customers_served_today_;

        check_queue_time_today_ = 0.0;
        vax_queue_time_today_ = 0.0;
        total_time_today_ = 0.0;
        customers_served_today_ = 0;

        station_.reset();
    }
}

void Simulation::get_statistics() {
    std::cout << "TOTAL STATISTICS:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "AVERAGE CUSTOMERS SERVED PER DAY: "
              << (total_customers_served_ / num_days_) << '\n';
    std::cout << "AVERAGE CHECK-IN QUEUE TIME: "
              << (ave_check_queue_time_ / total_customers_served_)
              << " MINUTES\n";
    std::cout << "AVERAGE VACCINATION QUEUE TIME: "
              << (ave_vax_queue_time_ / total_customers_served_)
              << " MINUTES\n";
    std::cout << "AVERAGE TOTAL TIME: "
              << (ave_total_time_ / total_customers_served_) << " MINUTES\n";
}

void Simulation::shuffle_customers() {
    std::shuffle(customers_.begin(), customers_.end(),
                 std::default_random_engine(0));
}

void Simulation::sort_customers() {
    std::sort(customers_.begin(), customers_.end(),
              [](Customer* c1, Customer* c2) {
                  return (std::floor(c1->get_wait_time()) ==
                          std::floor(c2->get_wait_time()))
                             ? (c1->is_senior() > c2->is_senior())
                             : (c1->get_wait_time() < c2->get_wait_time());
              });
}

void Simulation::assign_seniors() {

    int percentage_seniors = MAX_CUSTOMERS * SENIOR_PERCENTAGE;
    for (unsigned int i = 0; i < MAX_CUSTOMERS; i++) {

        auto c = new Customer();

        if (percentage_seniors) {
            c->make_senior();
            percentage_seniors--;
        }
        customers_.push_back(c);
    }
}

void Simulation::assign_phase_times() {

    double total_arrival_time = arrival_times_rng_.get();
    for (auto c : customers_) {

        c->set_arrival_time(total_arrival_time * MINUTES_PER_HOUR);
        c->set_check_in_time(check_in_times_rng_.get());
        c->set_vaccination_time(vaccination_times_rng_.get() *
                                MINUTES_PER_HOUR);
        total_arrival_time += arrival_times_rng_.get();
    }
}

void Simulation::simulate_queue() {

    unsigned int tick = 0;
    double wait_time = customers_.front()->get_wait_time();

#ifdef VERBOSE
    std::cout << " ID  | S |  ARR   | CHK  |  VAX  |\n";
    std::cout << "----------------------------------\n";
#endif

    while (tick < MINUTES_PER_HOUR * HOURS_OF_OPERATION &&
           !customers_.empty()) {

        station_.poll(tick);

        if (wait_time <= tick && customers_.size() && add_to_line(tick)) {

            // if there are still customers left, keep looping
            if (!customers_.empty()) {
                wait_time = customers_.front()->get_wait_time();
            }

        } else {
            tick++;
        }
    }
}

bool Simulation::add_to_line(int tick) {

    int available_station_num = station_.find_available_station();

    if (available_station_num != -1) {

        auto c = customers_.front();
#ifdef VERBOSE
        std::cout << *c << '\n';
#endif
        station_.vaccinate(c, available_station_num);

        customers_served_today_++;
        check_queue_time_today_ += c->get_check_in_time();
        vax_queue_time_today_ += (tick % 60);
        total_time_today_ += ((tick % 60) + c->get_vaccination_time());

        customers_.pop_front();

        return true;
    }
    return false;
}
