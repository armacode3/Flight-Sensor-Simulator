#include "physics_engine.h"

// Constructor
PhysicsEngine::PhysicsEngine() {
    trueAltitude = 0.0;
    trueVelocity = 0.0;
    acceleration = 0.0;
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
    double dragMagnitude = 0.5 * AIR_DENSITY * (trueVelocity * trueVelocity) * currentDragCoefficent * CROSS_SECTIONAL_AREA;
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