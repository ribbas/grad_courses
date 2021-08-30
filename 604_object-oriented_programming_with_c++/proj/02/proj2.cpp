/*
 * proj2.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the driver function for Mini-project #2.
 *
 */

#include "simulation.hpp"

int main() {

    // simulate 5 days
    Simulation sim(5);
    sim.simulate_days();
    sim.get_statistics();

    return 0;
}
