#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include "constants.h"
#include "flight_computer.h"
#include "physics_engine.h"
#include "sensors.h"

using boost::asio::ip::udp;

int main() {
    // Initialize components
    PhysicsEngine engine;
    FlightComputer computer;
    Sensors sensors;

    double flightTime = 0.0;
    bool parachuteDeployed = false;

    std::ofstream dataFile("output.csv");

    if (!dataFile.is_open()) {
        std::cerr << "ERROR: Unable to open file for writing.\n";
        return 1;
    }

    dataFile << "Time,TrueAlt,EstAlt,TrueVel,EstVel,EstAngle,TrueLat,TrueLon,EstLat,EstLon\n";

    try{
        // "manager" object that provides all the I/O services
        boost::asio::io_context io_context;

        // "doorway" Represents a socket for UDP
        udp::socket socket(io_context);

        // Tell the socket where to send data
        udp::endpoint remoteEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), 9000);
        socket.open(udp::v4());

        // Main loop
        while (engine.getTrueAltitude() >= 0.0 || flightTime < 1.0) {
            // Update real-world physics
            engine.updateState(flightTime, parachuteDeployed);

            // Update sensors based on new calculations
            sensors.update(engine.getAcceleration(), engine.getTrueAltitude(), engine.getTrueLatitude(), engine.getTrueLongitude());

            // Update flight computer with noisy sensor data
            computer.updateState(sensors.getNoisyAcceleration(), sensors.getBarometerAltitude(), sensors.isBarometerReady(), sensors.getNoisyAngularVelocity(), sensors.getNoisyLatitude(), sensors.getNoisyLongitude(), sensors.isGpsReady());

            // Flight computer makes decision
            if (!parachuteDeployed && computer.shouldDeployParachute()) {
                parachuteDeployed = true;
                std::cout << "--------------------------------------------------" << std::endl;
                printf("DEPLOY PARACHUTE command issued at %.2f s\n", flightTime);
                printf("True Alt: %.2f m | Estimated Alt: %.2f m\n", engine.getTrueAltitude(), computer.getEstimatedAltitude());
                std::cout << "--------------------------------------------------" << std::endl;
            }

            // print data
            if (static_cast<int>(flightTime / TIME_STEP) % 10 == 0) {
                printf("Time: %.2f s | True Alt: %.2f m | Est Alt: %.2f m | True Vel: %.2f m/s | Est Vel: %.2f m/s | Angle: %.2f\n",
                    flightTime, engine.getTrueAltitude(), computer.getEstimatedAltitude(), engine.getTrueVelocity(), computer.getEstimatedVelocity(), computer.getEstimatedAngle());
            }

            // Update Time
            flightTime += TIME_STEP;

            dataFile << 
                flightTime << "," << 
                engine.getTrueAltitude() << "," << 
                computer.getEstimatedAltitude() << "," << 
                engine.getTrueVelocity() << "," << 
                computer.getEstimatedVelocity() << "," <<
                computer.getEstimatedAngle() << "," <<
                engine.getTrueLatitude() << "," <<
                engine.getTrueLongitude() << "," <<
                computer.getEstimatedLatitude() << "," <<
                computer.getEstimatedLongitude() << "\n";

            // Make message to send through socket
            std::string message = std::to_string(flightTime) + "," + std::to_string(engine.getTrueAltitude()) + "," + std::to_string(computer.getEstimatedAltitude());

            // Send message to remote endpoint made before
            socket.send_to(boost::asio::buffer(message), remoteEndpoint);

            // Safety break
            if (flightTime > SIMULATION_DURATION) {
                std::cout << "Simulation timed out." << std::endl;
                break;
            }
        }

        printf("Landed at %.2f s. Final Altitude: %.2f m\n", flightTime, engine.getTrueAltitude());
    } catch(std::exception& e) {
        std::cerr << "Networking Error: " << e.what() << std::endl;
        return 1;
    }
    dataFile.close();

    return 0;
}

