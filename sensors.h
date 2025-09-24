#pragma once
#include "constants.h"
#include <random>

class Sensors {
private:
    double noisyAcceleration;
    double barometerAltitude;
    double noisyAngularVelocity;
    double noisyLatitude;
    double noisyLongitude;
    int updateCounter;

public:
    // Constructor
    Sensors();

    // Main update funciton
    void update(double trueAcceleration, double trueAltitude, double trueLatitude, double trueLongitude);

    // Checks if barometer is ready
    bool isBarometerReady() const;
    bool isGpsReady() const;

    // Getters
    double getNoisyAcceleration() const;
    double getBarometerAltitude() const;
    double getNoisyAngularVelocity() const;
    double getNoisyLatitude() const;
    double getNoisyLongitude() const;
};