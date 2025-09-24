#include <iostream>
#include <cstdio>
#include "constants.h"
#include "flight_computer.h"
#include "physics_engine.h"
#include "sensors.h"

int main() {
    // Initialize components
    PhysicsEngine engine;
    FlightComputer computer;
    Sensors sensors;

    double flightTime = 0.0;
    bool parachuteDeployed = false;

    // Main loop
    while (engine.getTrueAltitude() >= 0.0 || flightTime < 1.0) {
        // Update real-world physics
        engine.updateState(flightTime, parachuteDeployed);

        // Update sensors based on new calculations
        sensors.update(engine.getAcceleration(), engine.getTrueAltitude());

        // Update flight computer with noisy sensor data
        computer.updateState(sensors.getNoisyAcceleration(), sensors.getBarometerAltitude(), sensors.isBarometerReady());

        // Flight computer makes decision
        if (!parachuteDeployed && computer.shouldDeployParachute()) {
            parachuteDeployed = true;
            std::cout << "--------------------------------------------------" << std::endl;
            printf("DEPLOY PARACHUTE command issued at %.2f s\n", flightTime);
            printf("True Alt: %.2f m | Estimated Alt: %.2f m\n", engine.getTrueAltitude(), computer.getEstimatedAltitude());
            std::cout << "--------------------------------------------------" << std::endl;
        }

        // print data
        if (static_cast<int>(flightTime / TIME_STEP) % 10 == 0) {
            printf("Time: %.2f s | True Alt: %.2f m | Est Alt: %.2f m | True Vel: %.2f m/s | Est Vel: %.2f m/s\n",
                   flightTime, engine.getTrueAltitude(), computer.getEstimatedAltitude(), engine.getTrueVelocity(), computer.getEstimatedVelocity());
        }

        // Update Time
        flightTime += TIME_STEP;

        // Safety break
        if (flightTime > SIMULATION_DURATION) {
            std::cout << "Simulation timed out." << std::endl;
            break;
        }
    }

    printf("Landed at %.2f s. Final Altitude: %.2f m\n", flightTime, engine.getTrueAltitude());

    return 0;
}