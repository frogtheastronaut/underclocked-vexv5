#include "motion_profiling.hpp"
#include <cmath>

const double WHEEL_DIAMETER = 2.75; // inches
const double TICKS_PER_REV = 360.0; // encoder ticks per revolution

// Helper to convert distance (in inches) to encoder ticks
double inchesToTicks(double inches) {
  return (inches / (M_PI * WHEEL_DIAMETER)) * TICKS_PER_REV;
}

// Calculate motion state for trapezoidal velocity profile
MotionState trapezoidalProfile(double t, double distance, double v_max, double a_max) {
  double t_a = v_max / a_max;                            // accel time
  double d_a = 0.5 * a_max * t_a * t_a;                  // accel distance
  double d_total = distance;
  double d_c = d_total - 2 * d_a;                        // cruise distance

  // If we never reach v_max (triangle profile)
  if (d_c < 0) {
    v_max = std::sqrt(a_max * d_total);
    t_a = v_max / a_max;
    d_a = 0.5 * a_max * t_a * t_a;
    d_c = 0;
  }

  double t_c = (d_c > 0) ? (d_c / v_max) : 0;
  double t_total = 2 * t_a + t_c;

  double pos = 0.0;
  double vel = 0.0;

  // Acceleration phase
  if (t < t_a) {
    vel = a_max * t;
    pos = 0.5 * a_max * t * t;
  }
  // Cruise phase
  else if (t < t_a + t_c) {
    vel = v_max;
    pos = d_a + v_max * (t - t_a);
  }
  // Deceleration phase
  else if (t < t_total) {
    double td = t - t_a - t_c;
    vel = v_max - a_max * td;
    pos = d_a + d_c + (v_max * td - 0.5 * a_max * td * td);
  }
  // Done
  else {
    pos = d_total;
    vel = 0.0;
  }

  return {pos, vel};
}

void moveBot(pros::Motor& leftMotor, pros::Motor& rightMotor, double distance_in_inches, double v_max_in_ips, double a_max_in_ips2) {
  const double dt = 0.01; // 10 ms loop time
  double distance_ticks = inchesToTicks(distance_in_inches);
  double t = 0.0;

  // Convert linear velocity (inches/sec) to ticks/sec
  double v_max_ticks = inchesToTicks(v_max_in_ips);
  double a_max_ticks = inchesToTicks(a_max_in_ips2);

  // Reset encoders
  leftMotor.tare_position();
  rightMotor.tare_position();

  // Run the motion profile
  while (true) {
    MotionState state = trapezoidalProfile(t, distance_ticks, v_max_ticks, a_max_ticks);

    // Move motors with velocity in ticks/s -> rpm
    double rpm = (state.velocity / TICKS_PER_REV) * 60.0;
    leftMotor.move_velocity(rpm);
    rightMotor.move_velocity(rpm);

    // Exit when done
    if (state.position >= distance_ticks) break;

    pros::delay(dt * 1000);
    t += dt;
  }

  leftMotor.move_velocity(0);
  rightMotor.move_velocity(0);
}
