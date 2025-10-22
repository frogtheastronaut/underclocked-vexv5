#include "main.h"
#include "robot.hpp"

void autonomous() {
	// Simple demo autonomous: drive forward, turn in place, stop
	// Drive forward at 10% for 2 seconds
	left_mtr1.move(10);
	left_mtr2.move(10);
	left_mtr3.move(10);
	right_mtr1.move(10);
	right_mtr2.move(10);
	right_mtr3.move(10);
	pros::delay(2000);

	// Turn in place: left forward, right reverse at 10% for 2 seconds
	left_mtr1.move(10);
	left_mtr2.move(10);
	left_mtr3.move(10);
	right_mtr1.move(-10);
	right_mtr2.move(-10);
	right_mtr3.move(-10);
	pros::delay(2000);

	// Stop
	left_mtr1.move(0);
	left_mtr2.move(0);
	left_mtr3.move(0);
	right_mtr1.move(0);
	right_mtr2.move(0);
	right_mtr3.move(0);
}
