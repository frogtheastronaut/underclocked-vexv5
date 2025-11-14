#include "robot.hpp"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive motors
pros::Motor left_mtr1(1, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_mtr2(2, pros::E_MOTOR_GEARSET_18, false);
pros::Motor left_mtr3(3, pros::E_MOTOR_GEARSET_18, false);

pros::Motor right_mtr1(4, pros::E_MOTOR_GEARSET_18, true);
pros::Motor right_mtr2(5, pros::E_MOTOR_GEARSET_18, true);
pros::Motor right_mtr3(6, pros::E_MOTOR_GEARSET_18, true);

pros::Motor intake(7, pros::E_MOTOR_GEARSET_18, true);
pros::Motor conveyer(8, pros::E_MOTOR_GEARSET_18, false);

pros::Motor flapper(9, pros::E_MOTOR_GEARSET_18, false);

bool isFlapperActive = false;

// DriveMovement Implementation
DriveMovement::DriveMovement(double wheelDiameterInches, double trackWidthInches)
    : wheelDiameter(wheelDiameterInches), trackWidth(trackWidthInches) {}

void DriveMovement::setWheelDiameter(double inches) {
    wheelDiameter = inches;
}

void DriveMovement::setTrackWidth(double inches) {
    trackWidth = inches;
}

double DriveMovement::inchesToMeters(double inches) {
    return inches * 0.0254;
}

double DriveMovement::metersToInches(double meters) {
    return meters / 0.0254;
}

void DriveMovement::stopMotors() {
    left_mtr1.move(0);
    left_mtr2.move(0);
    left_mtr3.move(0);
    right_mtr1.move(0);
    right_mtr2.move(0);
    right_mtr3.move(0);
}

void DriveMovement::moveDistance(double meters, int velocity) {
    double distanceInches = metersToInches(meters);
    double wheelCircumference = M_PI * wheelDiameter;
    double rotations = distanceInches / wheelCircumference;
    double motorDegrees = rotations * 360.0;

    double startLeft = left_mtr1.get_position();
    double startRight = right_mtr1.get_position();

    // Move forward
    left_mtr1.move(velocity);
    left_mtr2.move(velocity);
    left_mtr3.move(velocity);
    right_mtr1.move(velocity);
    right_mtr2.move(velocity);
    right_mtr3.move(velocity);

    // wait until distance reached
    while ((left_mtr1.get_position() - startLeft < motorDegrees) ||
           (right_mtr1.get_position() - startRight < motorDegrees)) {
        pros::delay(5);
    }

    stopMotors();
}

void DriveMovement::turnDegrees(double degrees, int velocity) {
    // Calculate arc length for turn
    double turnRadius = trackWidth / 2.0;
    double arcLength = (fabs(degrees) / 360.0) * 2.0 * M_PI * turnRadius;
    double wheelCircumference = M_PI * wheelDiameter;
    double rotations = arcLength / wheelCircumference;
    double motorDegrees = rotations * 360.0;

    // Determine direction
    int leftVel = (degrees > 0) ? velocity : -velocity; // left turn positive
    int rightVel = -leftVel;                             // opposite side

    // Record starting positions
    double startLeft = left_mtr1.get_position();
    double startRight = right_mtr1.get_position();

    // Start turning
    left_mtr1.move(leftVel);
    left_mtr2.move(leftVel);
    left_mtr3.move(leftVel);
    right_mtr1.move(rightVel);
    right_mtr2.move(rightVel);
    right_mtr3.move(rightVel);

    // Wait until turn complete
    while ((fabs(left_mtr1.get_position() - startLeft) < motorDegrees) ||
           (fabs(right_mtr1.get_position() - startRight) < motorDegrees)) {
        pros::delay(5);
    }

    stopMotors();
}

void toggleFlapper() {
    if (isFlapperActive) {
        flapper.move(-10);
        pros::delay(500);
        flapper.move(0);
        isFlapperActive = false;
    } else {
        flapper.move(10);
        pros::delay(500);
        flapper.move(0);
        isFlapperActive = true;
    }
}


