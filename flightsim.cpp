#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // srand libarry
#include "constants.h"
#include ""

class Sensors {

};

class FlightComputer {

};




// Physics Engine
int main() {
    srand(time(0));

    // State Variables
    double trueAltitude = 0.0;
    double trueVelocity = 0.0;
    double acceleration = 0.0;

    // Flight Computer (estimates)
    double estimatedAltitude = 0.0;
    double estimatedVelocity = 0.0;
    double previousEstimatedVelocity;
    double barometerAltitude = 0.0;

    // Current variable that change during flight
    double flightTime = 0.0;
    double currentMass = ROCKET_MASS_FULL;
    double currenDragCoefficient = DRAG_COEFFICIENT_ROCKET;
    bool parachuteDeployed = false;

    // Main Simulation Loop
    while (flightTime <= SIMULATION_DURATION){
        // Detect Apogee (Highest point)
        if (!parachuteDeployed && previousEstimatedVelocity > 0 && estimatedVelocity < 0) {
            printf("Parachute Deployed\n");
            parachuteDeployed = true;
        }

        // After apogee is detected, the parachute deploys
        if (parachuteDeployed) {
            currenDragCoefficient = DRAG_COEFFICIENT_PARACHUTE;
        }

        // Update rocket state based on flight time
        if (flightTime >= ENGINE_BURN_TIME) {
            currentMass = ROCKET_MASS_EMPTY;
        }
        
        // Calculate Forces
        double fGravity = currentMass * GRAVITY;

        double fThrust = 0.0;
        if (flightTime < ENGINE_BURN_TIME) {
            fThrust = ENGINE_THRUST;
        }

        // Calculate the drag force magnitude and direciton
        double dragMagnitude = (0.5 * AIR_DENSITY * (trueVelocity * trueVelocity) * currenDragCoefficient * CROSS_SECTIONAL_AREA);
        
        double fDrag = 0.0;
        if (trueVelocity > 0) {
            fDrag = -dragMagnitude; // Oppose upward motion
        } else {
            fDrag = dragMagnitude; // Oppose downward motion
        }

        // Determine Net Force and Acceleration
        double netForce = fThrust + fGravity + fDrag;
        acceleration = netForce / currentMass;

        // Find New State Using Euler Method
        trueVelocity = trueVelocity + (acceleration * TIME_STEP);
        trueAltitude = trueAltitude + (trueVelocity * TIME_STEP);

        // Update previous velocity
        previousEstimatedVelocity = estimatedVelocity;

        estimatedVelocity = estimatedVelocity + (noisyAcceleration * TIME_STEP);
        estimatedAltitude = estimatedAltitude + (estimatedVelocity * TIME_STEP);

        // Generate a noisy reading for accelerometer based on truth
        double accelerometrNoise = ((static_cast<double>(rand() / RAND_MAX)) * 0.4) - 0.2; // Range (-0.2 to 0.2) m/s^2
        double noisyAcceleration = acceleration + accelerometrNoise;

        if (static_cast<int>(flightTime / TIME_STEP) % 10 == 0) {
            // Generate a noisy reading for Barometer
            double barometerNoise = ((static_cast<double>(rand()) / RAND_MAX) * 10.0) - 5.0; // Range (-5.0 to 5.0) meters
            barometerAltitude = trueAltitude + barometerNoise;
        }

        // Stop simulation if rocket has landed
        if (trueAltitude < 0.0 && flightTime > ENGINE_BURN_TIME) {
            printf("Time: %.2f s | LANDED\n", flightTime);
            break; // Exit loop
        }
        
        // Implementing the Kalman filter
        double error = barometerAltitude - estimatedAltitude; // Calculate error (difference)
        estimatedAltitude = estimatedAltitude + (error * 0.1); // Update estimate by adding a small fraction of error

        // Print current state every 10 steps
        if (static_cast<int>(flightTime / TIME_STEP) % 10 == 0) {
            printf("Time: %.2f s | True Alt: %.2f m | Est Alt: %.2f m | True Vel: %.2f m/s | Est Vel: %.2f m/s\n", flightTime, trueAltitude, estimatedAltitude, trueVelocity, estimatedVelocity);
        }

        // Update Time
        flightTime += TIME_STEP;
    }
    return 0;
}