#include "station.hpp"

VaccinationStation::VaccinationStation() {
    stations_.fill(nullptr);
}

VaccinationStation::~VaccinationStation() {
    reset();
}

void VaccinationStation::reset() {
    for (int i = 0; i < NUM_STATIONS; i++) {
        delete stations_[i];
        stations_[i] = nullptr;
    }
}

void VaccinationStation::vaccinate(Customer* customer,
                                   int available_station_num) {
    stations_[available_station_num] = customer;
}

int VaccinationStation::find_available_station() {
    for (int i = 0; i < NUM_STATIONS; i++) {
        if (!stations_[i]) {
            return i;
        }
    }

    return -1;
}

bool VaccinationStation::is_customer_done(int station_num, int tick) {
    return stations_[station_num]->get_total_time() < tick;
}

void VaccinationStation::poll(int tick) {

    for (int i = 0; i < NUM_STATIONS; i++) {
        if (stations_[i] && is_customer_done(i, tick)) {
            delete stations_[i];
            stations_[i] = nullptr;
        }
    }
}
