#ifndef WAITING_LINE_HPP
#define WAITING_LINE_HPP

#include <array>
#include <iostream>

#include "customer.hpp"

class VaccinationStation {
public:
    VaccinationStation() : capacity_(3) {
        for (int i = 0; i < 3; i++) {
            customers_in_stations_[i] = nullptr;
        }
    }

    bool vaccinate(Customer* customer, int tick, double total_time) {
        if (capacity_) {
            customers_in_stations_[3 - capacity_] = customer;
            std::cout << "putting in station "
                      << customers_in_stations_[3 - capacity_] << " capacity "
                      << capacity_ << '\n';
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
                  << customers_in_stations_[station_num]->get_total_time()
                  << ' ' << total_time << ' ' << tick << '\n';
        return (customers_in_stations_[station_num]->get_total_time()) < tick;
    }

    void send_home(int tick, double total_time) {

        if (capacity_ != 3) {
            for (int i = 0; i < customers_in_stations_.size(); i++) {
                if (customers_in_stations_[i] &&
                    check_station_time(i, tick, total_time)) {
                    std::cout
                        << "found someone " << customers_in_stations_[i] << ' '
                        << customers_in_stations_[i]->get_total_time() << ' '
                        << tick << '\n';
                    delete customers_in_stations_[i];
                    customers_in_stations_[i] = nullptr;
                    capacity_++;
                }
            }
        }
    }

private:
    std::array<Customer*, 3> customers_in_stations_;
    int capacity_;
};

#endif
