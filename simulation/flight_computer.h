#pragma once
#include "constants.h"

// "Brain"
class FlightComputer {
private:
    double estimatedAltitude;
    double estimatedVelocity;
    double previousEstimatedVelocity;
    double estimatedAngle;
    double estimatedLongitude;
    double estimatedLatitude;

public:
    // Constructor
    FlightComputer();

    // Main update funciton 
    void updateState(double noisyAcceleration, double barometerAltitude, bool isBarometerReady, double noisyAngleVelocity, double noisyLatitude, double noisyLongitude, bool isGpsReady);

    // Function to check apogee condition
    bool shouldDeployParachute() const;

    // Getter functions
    double getEstimatedAltitude() const;
    double getEstimatedVelocity() const;
    double getEstimatedAngle() const;
    double getEstimatedLatitude() const;
    double getEstimatedLongitude() const;
};