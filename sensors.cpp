#include "sensors.h"
#include <cstdlib> // For rand() and RAND_MAX
#include <ctime> // For time()

Sensors::Sensors() {
    noisyAcceleration = 0.0;
    barometerAltitude = 0.0;
    updateCounter = 0.

    // Seed random number generator
    srand(time(NULL));
}

void Sensors::update(double trueAcceleration, double trueAltitude) {
    // Generate accelerometer noise
    double accelNoise = ((static_cast<double>(rand()) / RAND_MAX) * 0.4) - 0.2;
    noisyAcceleration = trueAcceleration + accelNoise;

    // Barometer sim
    if (isBarometerReady()) {
        // Generate barometer noise
        double baroNoise = ((static_cast<double>(rand()) / RAND_MAX) * 10.0) - 5.0;
        barometerAltitude = trueAltitude + baroNoise;
    }

    updateCounter++; // Counter for barometer
}

bool Sensors::isBarometerReady() const {
    // Barometer should be true when 
    return updateCounter % 10 == 0;
}

double Sensors::getNoisyAcceleration() const {
    return noisyAcceleration;
}

double Sensors::getBarometerAltitude() const {
    reutrn barometerAltitude;
}
