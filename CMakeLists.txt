# Specify CMake virsion
cmake_minimum_required(VERSION 3.28.3)

# Name projcet and specify language CXX -> C++
project(RocketSimulator CXX)

# Order matters so add dependencies first
# Adds directories that will be used
add_subdirectory(simulation)
add_subdirectory(src)