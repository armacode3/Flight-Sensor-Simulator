#include <iostream>
#include <cstdio>
#include <fstream>
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

    std::ofstream dataFile("output.csv");

    if (!dataFile.is_open()) {
        std::cerr << "ERROR: Unable to open file for writing.\n";
        return 1;
    }

    dataFile << "Time,TrueAlt,EstAlt,TrueVel,EstVel,EstAngle,TrueLat,TrueLon,EstLat,EstLon\n";

    // Main loop
    while (engine.getTrueAltitude() >= 0.0 || flightTime < 1.0) {
        // Update real-world physics
        engine.updateState(flightTime, parachuteDeployed);

        // Update sensors based on new calculations
        sensors.update(engine.getAcceleration(), engine.getTrueAltitude(), engine.getTrueLatitude(), engine.getTrueLongitude());

        // Update flight computer with noisy sensor data
        computer.updateState(sensors.getNoisyAcceleration(), sensors.getBarometerAltitude(), sensors.isBarometerReady(), sensors.getNoisyAngularVelocity(), sensors.getNoisyLatitude(), sensors.getNoisyLongitude(), sensors.isGpsReady());

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
            printf("Time: %.2f s | True Alt: %.2f m | Est Alt: %.2f m | True Vel: %.2f m/s | Est Vel: %.2f m/s | Angle: %.2f\n",
                   flightTime, engine.getTrueAltitude(), computer.getEstimatedAltitude(), engine.getTrueVelocity(), computer.getEstimatedVelocity(), computer.getEstimatedAngle());
        }

        // Update Time
        flightTime += TIME_STEP;

        dataFile << 
            flightTime << "," << 
            engine.getTrueAltitude() << "," << 
            computer.getEstimatedAltitude() << "," << 
            engine.getTrueVelocity() << "," << 
            computer.getEstimatedVelocity() << "," <<
            computer.getEstimatedAngle() << "," <<
            engine.getTrueLatitude() << "," <<
            engine.getTrueLongitude() << "," <<
            computer.getEstimatedLatitude() << "," <<
            computer.getEstimatedLongitude() << "\n";

        // Safety break
        if (flightTime > SIMULATION_DURATION) {
            std::cout << "Simulation timed out." << std::endl;
            break;
        }
    }

    printf("Landed at %.2f s. Final Altitude: %.2f m\n", flightTime, engine.getTrueAltitude());

    dataFile.close();

    return 0;
}