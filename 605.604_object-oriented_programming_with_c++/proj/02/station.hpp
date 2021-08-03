#ifndef STATION_HPP
#define STATION_HPP

#include <array>
#include <iostream>

#include "customer.hpp"

const unsigned int NUM_STATIONS = 3;

class VaccinationStation {
public:
    VaccinationStation() : capacity_(NUM_STATIONS) {
        for (int i = 0; i < NUM_STATIONS; i++) {
            customers_in_stations_[i] = nullptr;
        }
    }

    bool vaccinate(Customer* customer, int tick, double total_time) {
        if (capacity_) {
            customers_in_stations_[NUM_STATIONS - capacity_] = customer;
            std::cout << "putting in station " << NUM_STATIONS - capacity_
                      << ' ' << customers_in_stations_[NUM_STATIONS - capacity_]
                      << " capacity " << capacity_ << '\n';
            capacity_--;
            return true;
        }

        return false;
    }

    bool is_empty() {
        return capacity_;
    }

    bool check_station_time(int station_num, int tick, double total_time) {
        std::cout << customers_in_stations_[station_num] << ' '
                  << customers_in_stations_[station_num]->get_wait_time() << ' '
                  << total_time << ' ' << tick << '\n';
        return (customers_in_stations_[station_num]->get_wait_time()) < tick;
    }

    void send_home(int tick, double total_time) {

        if (capacity_ != NUM_STATIONS) {
            for (int i = 0; i < NUM_STATIONS; i++) {
                if (customers_in_stations_[i] &&
                    check_station_time(i, tick, total_time)) {
                    std::cout
                        << "found someone " << customers_in_stations_[i] << ' '
                        << customers_in_stations_[i]->get_wait_time() << ' '
                        << tick << '\n';
                    delete customers_in_stations_[i];
                    customers_in_stations_[i] = nullptr;
                    capacity_++;
                }
            }
        }
    }

private:
    std::array<Customer*, NUM_STATIONS> customers_in_stations_;
    int capacity_;
};

#endif
