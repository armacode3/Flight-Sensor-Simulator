#pragma once
#include "constants.h"

class FlightComputer {
private:
    double estimatedAltitude;
    double estimatedVelocity;
    double previousEstimatedVelocity;

public:
    // Constructor
    FlightComputer();

    // Main update funciton 
    void updateState(double noisyAcceleration, double barometerAltitude, bool isBarometerReady);

    // Function to check apogee condition
    bool shouldDeployParachute() const;

    // Getter functions
    double getEstimatedAltitude() const;
    double getEstimatedVelocity() const;
};