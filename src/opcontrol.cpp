#include "main.h"
#include "robot.hpp"
#include <cmath>

void opcontrol() {
	const int DEADZONE = 5; // joystick deadzone threshold
	const double SCALE = 0.7; // scale factor for joystick power
	const double MAX_ACCEL = 0.1; // max acceleration per control loop (0.05% per 20ms)
	bool autonRunning = false; // is auton running
	
	double currentLeftSpeed = 0;// current speed left
	double currentRightSpeed = 0;// current speed right

	double speedLimiter = 0.75; // its usually at 75% power unless button pressed

	while (true) {
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int forward = master.get_analog(ANALOG_LEFT_Y);

		if (std::abs(forward) < DEADZONE) forward = 0;
		if (std::abs(turn) < DEADZONE) turn = 0;

		double targetLeftSpeed = (forward + turn) * SCALE;
		double targetRightSpeed = (forward - turn) * SCALE;

		double deltaLeft = targetLeftSpeed - currentLeftSpeed;
		double deltaRight = targetRightSpeed - currentRightSpeed;

		// Clamp change to ±MAX_ACCEL
		if (std::abs(deltaLeft) > MAX_ACCEL * 127) 
			deltaLeft = (deltaLeft > 0 ? 1 : -1) * MAX_ACCEL * 127;
		if (std::abs(deltaRight) > MAX_ACCEL * 127) 
			deltaRight = (deltaRight > 0 ? 1 : -1) * MAX_ACCEL * 127;

		currentLeftSpeed += deltaLeft;
		currentRightSpeed += deltaRight;


		if (master.get_digital(DIGITAL_L1)) {
			conveyer.move(50);
			intake.move(50);
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		} 
		else if (master.get_digital(DIGITAL_L2)) {
			conveyer.move(-50);
			intake.move(-50);
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		} 
		else {
			conveyer.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
			conveyer.move(0);
			intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
			intake.move(0);
		}

		if (master.get_digital_new_press(DIGITAL_R1)) {
			toggleFlapper();
		}

		if (master.get_digital(DIGITAL_R2)) { // go zoom
			speedLimiter = 1.0;
		} else {
			speedLimiter = 0.75;
		}

		left_mtr1.move((int)(currentLeftSpeed * speedLimiter));
		left_mtr2.move((int)(currentLeftSpeed * speedLimiter));
		left_mtr3.move((int)(currentLeftSpeed * speedLimiter));

		right_mtr1.move((int)(currentRightSpeed * speedLimiter));
		right_mtr2.move((int)(currentRightSpeed * speedLimiter));
		right_mtr3.move((int)(currentRightSpeed * speedLimiter));

		if (master.get_digital_new_press(DIGITAL_UP) && !autonRunning) {
			autonRunning = true;
			autonomous();
			autonRunning = false;
		}

		pros::delay(20);
	}
}
