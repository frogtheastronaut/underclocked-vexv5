#include "pid.hpp"

PID::PID(double kp, double ki, double kd)
    : kp(kp), ki(ki), kd(kd), integral(0), prevError(0), firstRun(true) {

}

void PID::initialise(double kp, double ki, double kd) {
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
}

void PID::reset() {
    integral = 0;
    prevError = 0;
    firstRun = true;
}

double PID::calculate(double setpoint, double measured, double dt) {
    double error = setpoint - measured;
    integral += error * dt;
    double derivative = 0;
    if (!firstRun && dt > 0) {
        derivative = (error - prevError) / dt;
    }
    prevError = error;
    firstRun = false;
    return kp * error + ki * integral + kd * derivative;
}
