add_executable(simulator flightsim.cpp)

# Finds Boost package
find_package(Boost REQUIRED)
# Links simulation_engine and boost library to executable
target_link_libraries(simulator PRIVATE simulation_engine Boost::boost)