#pragma once
#include "constants.h"
#include <random>

class Sensors {
private:
    double noisyAcceleration;
    double barometerAltitude;
    int updateCounter;

public:
    // Constructor
    Sensors();

    // Main update funciton
    void update(double trueAcceleration, double trueAltitude);

    // Checks if barometer is ready
    bool isBarometerReady() const;

    // Getters
    double getNoisyAcceleration() const;
    double getBarometerAltitude() const;
};