#include "main.h"
#include "robot.hpp"
#include <cmath>
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Deadzone and scaling match the python implementation
	const int DEADZONE = 5;
	const double SCALE = 0.7; // scale factor applied to final speed

	while (true) {
		int turn = master.get_analog(ANALOG_LEFT_Y);   // axis1 in python
		int forward = master.get_analog(ANALOG_RIGHT_X); // axis3 in python

		if (std::abs(forward) < DEADZONE) forward = 0;
		if (std::abs(turn) < DEADZONE) turn = 0;

	double left_speed = (forward + turn) * SCALE;
	double right_speed = (forward - turn) * SCALE;

	// Use move(percent) which expects -127..127 style values
	left_mtr1.move((int)left_speed);
	left_mtr2.move((int)left_speed);
	left_mtr3.move((int)left_speed);

	right_mtr1.move((int)right_speed);
	right_mtr2.move((int)right_speed);
	right_mtr3.move((int)right_speed);

		// Intake / Conveyer controls
		if (master.get_digital(DIGITAL_L1)) {
			conveyer.move(80);
			intake.move(100);
			// ensure brake mode appropriate
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		} else if (master.get_digital(DIGITAL_L2)) {
			conveyer.move(-80);
			intake.move(-100);
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		} else {
			// conveyer hold position, intake coast
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			conveyer.move(0);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.move(0);
		}

		// Manual trigger for autonomous (like controller.buttonUp.pressed in python)
		if (master.get_digital(DIGITAL_UP)) {
			autonomous();
		}

		pros::delay(20);
	}
}
