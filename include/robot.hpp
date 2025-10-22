/**
 * robot.hpp
 *
 * Global robot hardware objects (motors, controller) used across src files.
 */
#ifndef UNDERCLOCKED_VEXV5_ROBOT_HPP
#define UNDERCLOCKED_VEXV5_ROBOT_HPP

#include "api.h"

// Controller
extern pros::Controller master;

// Drive motors (left: ports 1-3, right: ports 4-6)
extern pros::Motor left_mtr1;
extern pros::Motor left_mtr2;
extern pros::Motor left_mtr3;
extern pros::Motor right_mtr1;
extern pros::Motor right_mtr2;
extern pros::Motor right_mtr3;

// Intake & Conveyer
extern pros::Motor intake;
extern pros::Motor conveyer;

#endif // UNDERCLOCKED_VEXV5_ROBOT_HPP
