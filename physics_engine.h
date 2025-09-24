#pragma once
#include "constants.h" // Constants file

// "Body"
class PhysicsEngine {
private:
    double trueAltitude;
    double trueVelocity;
    double acceleration;
    double currentMass;
    double currentDragCoefficent;

public:
    // Constructor to initialize object
    PhysicsEngine();

    // Runs all physics calculations
    void updateState(double flightTime, bool parachuteDeployed);

    // Getter functions
    double getTrueAltitude() const;
    double getTrueVelocity() const;
    double getAcceleration() const;
};
