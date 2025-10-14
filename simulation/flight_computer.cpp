#include "flight_computer.h"

FlightComputer::FlightComputer() {
    estimatedAltitude = 0.0;
    estimatedVelocity = 0.0;
    previousEstimatedVelocity = 0.0;
    estimatedAngle = 0.0;
    // Initialize to known launch site coordinates
    estimatedLatitude = 28.608389;
    estimatedLongitude = -80.604333;
}

void FlightComputer::updateState(double noisyAcceleration, double barometerAltitude, bool isBarometerReady, double noisyAngularVelocity, double noisyLatitude, double noisyLongitude, bool isGpsReady) {
    // Store last velocity for next apogee check
    previousEstimatedVelocity = estimatedVelocity;

    // Update velocity and altitude estimates
    estimatedVelocity = estimatedVelocity + (noisyAcceleration * TIME_STEP);
    estimatedAltitude = estimatedAltitude + (estimatedVelocity * TIME_STEP);

    // Update the estimated angle based on gyro
    estimatedAngle = estimatedAngle + (noisyAngularVelocity * TIME_STEP);

    // Only correct altitude estimate when new barometer data is sent
    if (isBarometerReady) {
        double error = barometerAltitude - estimatedAltitude;
        // Nudge estimate 10% towards barometer reading
        estimatedAltitude = estimatedAltitude + (error * 0.1);
    }

    // When a new GPS fix is available, update position estimate
    if (isGpsReady) {
        estimatedLatitude = noisyLatitude;
        estimatedLongitude = noisyLongitude;
    }
}

bool FlightComputer::shouldDeployParachute() const {
    // Apogee is detected when velcity goes from positive to negative
    return previousEstimatedVelocity > 0 && estimatedVelocity <= 0;
}

double FlightComputer::getEstimatedAltitude() const {
    return estimatedAltitude;
}

double FlightComputer::getEstimatedVelocity() const {
    return estimatedVelocity;
}

double FlightComputer::getEstimatedAngle() const {
    return estimatedAngle;
}

double FlightComputer::getEstimatedLatitude() const {
    return estimatedLatitude;
}

double FlightComputer::getEstimatedLongitude() const {
    return estimatedLongitude;
}