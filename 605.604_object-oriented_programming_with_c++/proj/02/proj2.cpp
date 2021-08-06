#include "simulation.hpp"

int main() {

    Simulation sim(5);
    sim.simulate_days();
    sim.get_statistics();

    return 0;
}
