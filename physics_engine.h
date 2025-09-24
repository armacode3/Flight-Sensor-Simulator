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
    double trueAngle;
    double trueLatitude;
    double trueLongitude;

public:
    // Constructor to initialize object
    PhysicsEngine();

    // Runs all physics calculations
    void updateState(double flightTime, bool parachuteDeployed);

    // Getter functions
    double getTrueAltitude() const;
    double getTrueVelocity() const;
    double getAcceleration() const;
    double getTrueAngle() const;
    double getTrueLatitude() const;
    double getTrueLongitude() const;
};
