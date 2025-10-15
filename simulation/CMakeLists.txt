# Create a static library that will act as the target by specifying cpp files
add_library(simulation_engine STATIC flight_computer.cpp physics_engine.cpp sensors.cpp)

# Tells target where to find its own files
# PUBLIC allows this include directory to be available to any other targets that link with this one
target_include_directories(simulation_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})