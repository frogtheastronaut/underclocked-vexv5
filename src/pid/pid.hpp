#ifndef PID_H
#define PID_H

class PID {
public:
    PID(double kp, double ki, double kd);
    void initialise(double kp, double ki, double kd);
    void reset();
    double calculate(double setpoint, double measured, double dt);

private:
    double kp, ki, kd;
    double integral;
    double prevError;
    bool firstRun;
};

#endif // PID_H
