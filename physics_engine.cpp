#include "physics_engine.h"
#include <cmath>

// Constructor
PhysicsEngine::PhysicsEngine() {
    trueAltitude = 0.0;
    trueVelocity = 0.0;
    acceleration = 0.0;
    trueAngle = 0.0;

    // Launch Complex 39A, Kennedy Space Center, FL
    trueLatitude = 28.608389;
    trueLongitude = -80.604333;
    currentMass = ROCKET_MASS_FULL;
    currentDragCoefficent = DRAG_COEFFICIENT_ROCKET;
}

// UpdateState implementation
void PhysicsEngine::updateState(double flightTime, bool parachuteDeployed) {
    // Update rocket state
    if (flightTime >= ENGINE_BURN_TIME) {
        currentMass = ROCKET_MASS_EMPTY;
    }
    if (parachuteDeployed) {
        currentDragCoefficent = DRAG_COEFFICIENT_PARACHUTE;
    }

    // Calculate forces
    double fGravity = -currentMass * GRAVITY;
    double fThrust = (flightTime < ENGINE_BURN_TIME) ? ENGINE_THRUST : 0.0;
    
    // Calculate current air density for rockets true altitude
    double currentAirDensity = SEA_LEVEL_AIR_DENSITY * exp(-trueAltitude / 8500.0);
    
    // Use new density in drag calculation
    double dragMagnitude = 0.5 * currentAirDensity * (trueVelocity * trueVelocity) * currentDragCoefficent * CROSS_SECTIONAL_AREA;
    double fDrag = (trueVelocity > 0) ? -dragMagnitude : dragMagnitude;

    // Calculate net force and update acceleration
    double netForce = fThrust + fGravity + fDrag;
    acceleration = netForce / currentMass;

    // Find new state using Euler Method
    trueVelocity = trueVelocity + (acceleration * TIME_STEP);
    trueAltitude = trueAltitude + (trueVelocity * TIME_STEP);
}

// Getter implemenations
double PhysicsEngine::getTrueAltitude() const {
    return trueAltitude;
}

double PhysicsEngine::getTrueVelocity() const {
    return trueVelocity;
}

double PhysicsEngine::getAcceleration() const {
    return acceleration;
}

double PhysicsEngine::getTrueAngle() const {
    return trueAngle;
}

double PhysicsEngine::getTrueLatitude() const {
    return trueLatitude;
}

double PhysicsEngine::getTrueLongitude() const {
    return trueLongitude;
}