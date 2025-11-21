# Flight Sensor Simulator

A real-time rocket flight simulation suite designed to model sensor noise, test flight control algorithms, and visualize telemetry data. This project bridges high-performance C++ physics simulation with Python-based real-time visualization using UDP sockets.

## Features

* **Physics Engine**: Simulates vertical rocket flight kinematics, including drag, gravity, and mass variations.
* **Sensor Emulation**: Generates synthetic sensor data (Barometer, GPS, IMU) with configurable noise profiles to test filter robustness.
* **Flight Computer**: Implements state estimation (Altitude, Velocity, Orientation) and parachute deployment logic.
* **Real-Time Telemetry**: Streams flight data via UDP to a separate dashboard.
* **Visualization Tools**:
    * **Live GUI**: A PyQt5 dashboard showing real-time altitude, velocity, and trajectory.
    * **Post-Flight Analysis**: A matplotlib script for plotting detailed performance graphs from CSV logs.

## Project Structure

* `src/`: Main simulation entry point.
* `simulation/`: Core libraries for Physics, Sensors, and Flight Computer logic.
* `scripts/`: Python scripts for GUI visualization and data plotting.

## Prerequisites

### C++ Dependencies
* **C++ Compiler** (C++17 or later)
* **CMake** (3.28+)
* **Boost Libraries** (specifically `boost::asio` for UDP networking)

### Python Dependencies
* Python 3.x
* `PyQt5`
* `pyqtgraph`
* `pandas`
* `matplotlib`

```bash
pip install PyQt5 pyqtgraph pandas matplotlib
