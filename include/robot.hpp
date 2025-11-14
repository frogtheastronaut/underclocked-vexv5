/**
 * robot.hpp
 *
 * Global robot hardware objects (motors, controller) used across src files.
 */
#ifndef UNDERCLOCKED_VEXV5_ROBOT_HPP
#define UNDERCLOCKED_VEXV5_ROBOT_HPP

#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "api.h"

// Controller
extern pros::Controller master;

// Drive motors
extern pros::Motor left_mtr1;
extern pros::Motor left_mtr2;
extern pros::Motor left_mtr3;
extern pros::Motor right_mtr1;
extern pros::Motor right_mtr2;
extern pros::Motor right_mtr3;

// Intake & Conveyer
extern pros::Motor intake;
extern pros::Motor conveyer;

// Movement utility class
class DriveMovement {
public:
    DriveMovement(double wheelDiameterInches, double trackWidthInches);

    void setWheelDiameter(double inches);
    void setTrackWidth(double inches);

    void moveDistance(double meters, int velocity);
    void turnDegrees(double degrees, int velocity);

    void stopMotors(); // <-- add this declaration

private:
    double wheelDiameter;
    double trackWidth;

    double inchesToMeters(double inches);
    double metersToInches(double meters);
};

extern void toggleFlapper();

#endif // UNDERCLOCKED_VEXV5_ROBOT_HPP
