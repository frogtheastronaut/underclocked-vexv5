#ifndef MOTPROF_H
#define MOTPROF_H

#include "pros/motors.hpp"
#include "pros/rtos.hpp"

struct MotionState {
  double position; // in ticks
  double velocity; // in ticks/s
};

// convert inches to ticks
double inchesToTicks(double inches);

// compute velocity at time p
MotionState trapezoidalProfile(double t, double distance, double v_max, double a_max);

// move motors
void moveBot(pros::Motor& leftMotor, pros::Motor& rightMotor, double distance_in_inches, double v_max_in_ips, double a_max_in_ips2);

#endif // MOTPROF_H