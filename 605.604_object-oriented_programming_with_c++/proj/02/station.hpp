/*
 * station.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the declarations for the VaccinationStation class.
 *
 */

#ifndef STATION_HPP
#define STATION_HPP

#include "customer.hpp"
#include <array>

const unsigned int NUM_STATIONS = 3;

class VaccinationStation {
public:
    /* ---------- CONSTRUCTORS ---------- */
    VaccinationStation();

    /* ---------- DESTRUCTORS ---------- */
    ~VaccinationStation();

    /* ---------- PUBLIC METHODS ---------- */
    void reset();

    void vaccinate(Customer*, int);

    int find_available_station();

    void poll(int);

private:
    /* ---------- PRIVATE METHODS ---------- */
    bool is_customer_done(int, int);

    /* ---------- MEMBER ATTRIBUTES ---------- */
    std::array<Customer*, NUM_STATIONS> stations_;
};

#endif
