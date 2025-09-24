#include "flight_computer.h"

FlightComputer::FlightComputer() {
    estimatedAltitude = 0.0;
    estimatedVelocity = 0.0;
    previousEstimatedVelocity = 0.0;
}

void FlightComputer::updateState(double noisyAcceleration, double barometerAltitude, bool isBarometerReady) {
    // Store last velocity for next apogee check
    previousEstimatedVelocity = estimatedVelocity;

    // Update velocity and altitude estimates
    estimatedVelocity = estimatedVelocity + (noisyAcceleration * TIME_STEP);
    estimatedAltitude = estimatedAltitude + (estimatedVelocity * TIME_STEP);

    // Only correct altitude estimate when new barometer data is sent
    if (isBarometerReady) {
        double error = barometerAltitude - estimatedAltitude;
        // Nudge estimate 10% towards barometer reading
        estimatedAltitude = estimatedAltitude + (error * 0.1);
    }
}

bool FlightComputer::shouldDeployParachute() const {
    // Apogee is detected when velcity goes from positive to negative
    return previousEstimatedVelocity > 0 && estimatedVelocity <= 0;
}

double FlightComputer::getEstimatedAltitude() {
    return estimatedAltitude;
}

double FlightComputer::getEstimatedVelocity() {
    return estimatedVelocity;
}