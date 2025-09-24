#pragma once

// Simulation Parameters 
const double TIME_STEP = 0.01;                  // sec (Refresh Rate)
const double SIMULATION_DURATION = 300.0;       // sec (Total time to simulate)

// Physical & Environmental Constants
const double GRAVITY = -9.81;                   // m/s^2
const double AIR_DENSITY = 1.225;               // kg/m^3 (at sea level)

// Rocket Physical Parameters
const double ROCKET_MASS_FULL = 5.0;            // kg (Mass with engine)
const double ROCKET_MASS_EMPTY = 4.5;           // kg (Mass after fuel is spent)
const double ENGINE_THRUST = 300.0;             // N (Force engine produces)
const double ENGINE_BURN_TIME = 3.0;            // sec 
const double DRAG_COEFFICIENT_ROCKET = 0.75;    // (How aerodynamic the rocket body is)
const double DRAG_COEFFICIENT_PARACHUTE = 7.5;  // (How much drag the parachute creates)
const double CROSS_SECTIONAL_AREA = 0.008;      // m^2 (The area of the rocket pushing against the air)
