#include "sensors.h"
#include <cstdlib> // For rand() and RAND_MAX
#include <ctime> // For time()

Sensors::Sensors() {
    noisyAcceleration = 0.0;
    barometerAltitude = 0.0;
    updateCounter = 0;
    noisyAngularVelocity = 0.0;
    noisyLatitude = 0.0;
    noisyLongitude = 0.0;

    // Seed random number generator
    srand(time(NULL));
}

void Sensors::update(double trueAcceleration, double trueAltitude, double trueLatitude, double trueLongitude) {
    // Generate accelerometer noise
    double accelNoise = ((static_cast<double>(rand()) / RAND_MAX) * 0.4) - 0.2;
    noisyAcceleration = trueAcceleration + accelNoise;

    // Barometer sim
    if (isBarometerReady()) {
        // Generate barometer noise
        double baroNoise = ((static_cast<double>(rand()) / RAND_MAX) * 10.0) - 5.0;
        barometerAltitude = trueAltitude + baroNoise;
    }

    double gyroNoise = ((static_cast<double>(rand()) / RAND_MAX) * 0.2) - 0.1;
    noisyAngularVelocity = gyroNoise; 

    // GPS
    if (isGpsReady()) {
        // 90% chance GPS fix
        if ((rand() % 100) < 90) {
            // GPS noise is offset. 0.0001 degrees is roughly 11 meters
            double latNoise = ((static_cast<double>(rand()) / RAND_MAX) * 0.0002) - 0.0001;
            double lonNoise = ((static_cast<double>(rand()) / RAND_MAX) * 0.0002) - 0.0001;

            noisyLatitude = trueLatitude + latNoise;
            noisyLongitude = trueLongitude + lonNoise;
        }

        // 10% chance occurs nothing happens (GPS Failed)
    }


    updateCounter++; // Counter for barometer
}

bool Sensors::isBarometerReady() const {
    // Barometer should be true when 
    return updateCounter % 10 == 0;
}

bool Sensors::isGpsReady() const {
    return updateCounter % 100 == 0;
}

double Sensors::getNoisyAcceleration() const {
    return noisyAcceleration;
}

double Sensors::getBarometerAltitude() const {
    return barometerAltitude;
}

double Sensors::getNoisyAngularVelocity() const {
    return noisyAngularVelocity;
}

double Sensors::getNoisyLatitude() const {
    return noisyLatitude;
}

double Sensors::getNoisyLongitude() const {
    return noisyLongitude;
}
