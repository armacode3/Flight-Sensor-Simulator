#include <iostream>
#include <vector>

// Simulation Parameters 
const double TIME_STEP = 0.01;                  // sec (Refresh Rate)
const double SIMULATION_DURATION = 300.0;       // sec (Total time to simulate)

// Physical & Environmental Constants
const double GRAVITY = -9.81;                   // m/s^2
const double AIR_DENSITY = 1.225;               // kg/m^3 (at sea level)

// Rocket Physical Parameters
const double ROCKET_MASS_FULL = 5.0;            // kg (Mass with engine)
const double ROCKET_MASS_EMPTY = 4.5;           // kg (Mass after fuel is spent)
const double ENGINE_THRUST = 300.0;             // N (Force engine produces)
const double ENGINE_BURN_TIME = 3.0;            // sec 
const double DRAG_COEFFICIENT_ROCKET = 0.75;    // (How aerodynamic the rocket body is)
const double DRAG_COEFFICIENT_PARACHUTE = 7.5;  // (How much drag the parachute creates)
const double CROSS_SECTIONAL_AREA = 0.008;      // m^2 (The area of the rocket pushing against the air)

// Physics Engine
int main() {
    // State Variables
    double altitude = 0.0;
    double velocity = 0.0;
    double acceleration = 0.0;
    double flightTime = 0.0;

    // Current variable that change during flight
    double currentMass = ROCKET_MASS_FULL;
    double currenDragCoefficient = DRAG_COEFFICIENT_ROCKET;

    // Main Simulation Loop
    while (flightTime <= SIMULATION_DURATION){
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
        double dragMagnitude = (0.5 * AIR_DENSITY * (velocity * velocity) * currenDragCoefficient * CROSS_SECTIONAL_AREA);
        double fDrag = 0.0;
        if (velocity > 0) {
            fDrag = -dragMagnitude; // Oppose upward motion
        } else {
            fDrag = dragMagnitude // Oppose downward motion
        }

        // Determine Net Force and Acceleration
        double netForce = fThrust + fGravity + fDrag;
        acceleration = netForce / currentMass;

        // Find New State Using Euler Method
        velocity = velocity + (acceleration * TIME_STEP);
        altitude = altitude + (velocity * TIME_STEP);

        // Stop simulation if rocket has landed
        if (altitude < 0.0 & flightTime > ENGINE_BURN_TIME) {
            altitude = 0.0; // Set to ground level
            velocity = 0.0;
            acceleration = 0.0;
            printf("Time: %.2f s | LANDED\n", flightTime);
            break; // Exit loop
        }

        // Print current state every 10 steps
        if (static_cast<int>(flightTime / TIME_STEP) % 10 == 0) {
            printf("Time: %.2f s | Alt: %.2f m | vel: %.2f m/s | Accel: %.2f m/s^2\n", flightTime, altitude, velocity, acceleration);
        }

        // Update Time
        flightTime += TIME_STEP;
    }
    return 0;
}