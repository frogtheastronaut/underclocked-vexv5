#include "robot.hpp"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive motors
pros::Motor left_mtr1(1, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_mtr2(2, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_mtr3(3, pros::E_MOTOR_GEARSET_18, false);

pros::Motor right_mtr1(4, pros::E_MOTOR_GEARSET_18, false);
pros::Motor right_mtr2(5, pros::E_MOTOR_GEARSET_18, false);
pros::Motor right_mtr3(6, pros::E_MOTOR_GEARSET_18, false);

pros::Motor intake(7, pros::E_MOTOR_GEARSET_18, true);
pros::Motor conveyer(8, pros::E_MOTOR_GEARSET_18, false);
