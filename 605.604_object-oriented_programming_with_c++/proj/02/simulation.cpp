/*
 * simulation.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the implementation for the Simulation class.
 *
 */

#include "simulation.hpp"

/*
 * Default parameterized constructor
 *
 * Params:
 *  num_days <int>: number of days to simulate
 *  seed <int>: seed number
 *
 * Returns:
 *  None
 */
Simulation::Simulation(int num_days, int seed)
    : arrival_times_rng_(30.0, seed), check_in_times_rng_(1.0, 4.0, seed),
      vaccination_times_rng_(15.0, seed), num_days_(num_days),
      total_customers_served_(0), customers_served_today_(0),
      ave_check_queue_time_(0.0), ave_vax_queue_time_(0.0),
      ave_total_time_(0.0), check_queue_time_today_(0.0),
      vax_queue_time_today_(0.0), total_time_today_(0.0) {}

/*
 * Default destructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
Simulation::~Simulation() {
    // clear out the Customers deque
    for (auto i : customers_) {
        delete i;
        i = nullptr;
    }
}

/*
 * Simulate the system for num_days_ days
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Simulation::simulate_days() {

    // iterate num_days_ times
    for (int i = 0; i < num_days_; i++) {

        // assign SENIOR_PERCENTAGE of the Customers as seniors
        assign_seniors();
        // shuffle the Customers deque
        shuffle_customers();

        // linearly assign the arrival, check-in, and vaccination times for each
        // of the Customers
        assign_phase_times();
        // sort the Customers deque
        sort_customers();

        // simulate the system for 12 hours
        simulate_queue();

        // display statistics for the day
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

        // accumulate the daily statistics
        ave_check_queue_time_ += check_queue_time_today_;
        ave_vax_queue_time_ += vax_queue_time_today_;
        ave_total_time_ += total_time_today_;
        total_customers_served_ += customers_served_today_;

        // reset the daily statistics
        check_queue_time_today_ = 0.0;
        vax_queue_time_today_ = 0.0;
        total_time_today_ = 0.0;
        customers_served_today_ = 0;

        // reset the station
        station_.reset();
    }
}

/*
 * Display the total statistics of the simulation
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
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

/*
 * Shuffle the Customers deque using std::shuffle. The deque is shuffled after
 * the seniors are assigned to simulate a more uniform distribution
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Simulation::shuffle_customers() {
    std::shuffle(customers_.begin(), customers_.end(),
                 std::default_random_engine(0));
}

/*
 * Sort the Customers deque using std::sort and a custom comparator.
 * The comparison lambda function checks if the floor of the queue times of two
 * Customer objects are equal. If true, this simulates 2 Customers
 * simultaneously arriving in front of a station. The comparator then checks if
 * either of the Customers are senior. If both or neither are seniors, the first
 * Customer is prioritized. Else, the senior Customer gets priority. If the
 * floor of the queue times of the Customers are not equal, then they are
 * compared as expected
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Simulation::sort_customers() {
    std::sort(customers_.begin(), customers_.end(),
              [](Customer* c1, Customer* c2) {
                  return (std::floor(c1->get_wait_time()) ==
                          std::floor(c2->get_wait_time()))
                             ? (c1->is_senior() > c2->is_senior())
                             : (c1->get_wait_time() < c2->get_wait_time());
              });
}

/*
 * Initialize the Customers deque and assign SENIOR_PERCENTAGE of them as
 * seniors.
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
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

/*
 * Iterate through the initialized Customers deque and assign them their
 * arrival, check-in and vaccination times.
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Simulation::assign_phase_times() {

    // accumulation of the arrival times of all the Customers in 12 hours
    double total_arrival_time = arrival_times_rng_.get();
    for (auto c : customers_) {

        c->set_arrival_time(total_arrival_time * MINUTES_PER_HOUR);
        c->set_check_in_time(check_in_times_rng_.get());
        c->set_vaccination_time(vaccination_times_rng_.get() *
                                MINUTES_PER_HOUR);
        total_arrival_time += arrival_times_rng_.get();
    }
}

/*
 * Simulate the clock and iterate through all the Customers in the deque,
 * checking their predetermined queue times and the availability of the
 * stations.
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Simulation::simulate_queue() {

    unsigned int tick = 0;
    double wait_time = customers_.front()->get_wait_time();

#ifdef VERBOSE
    std::cout << " ID  | S |  ARR   | CHK  |  VAX  |\n";
    std::cout << "----------------------------------\n";
#endif

    // under the 12 hours constraint and the Customers deque is not empty
    while (tick < MINUTES_PER_HOUR * HOURS_OF_OPERATION &&
           !customers_.empty()) {

        // check stations for any Customers ready to exit
        station_.poll(tick);

        // `wait_time <= tick`: the Customer's assigned queue time is less than
        // the system's clock
        // `add_to_line(tick)`: Customer was added to a station
        if (wait_time <= tick && add_to_line(tick)) {

            // if there are still Customers left, keep looping
            if (!customers_.empty()) {
                wait_time = customers_.front()->get_wait_time();
            }

        } else {
            // progress the system's clock
            tick++;
        }
    }
}

/*
 * Add the front Customer to an available Station
 *
 * Params:
 *  tick <int>: current time on the simulation clock
 *
 * Returns:
 *  <bool>: true if Customer was added to a Station, false otherwise
 */
bool Simulation::add_to_line(int tick) {

    // get the available Station number
    int available_station_num = station_.find_available_station();

    // if an available Station was found
    if (available_station_num != -1) {

        auto c = customers_.front();
#ifdef VERBOSE
        std::cout << *c << '\n';
#endif
        // send the Customer to the station
        station_.vaccinate(c, available_station_num);

        // update the daily statistics with the current Customer
        customers_served_today_++;
        check_queue_time_today_ += c->get_check_in_time();
        vax_queue_time_today_ += (tick % 60);
        total_time_today_ += ((tick % 60) + c->get_vaccination_time());

        // pop the current Customer from the deque
        customers_.pop_front();

        return true;
    }
    return false;
}
