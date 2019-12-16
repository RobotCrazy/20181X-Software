#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift
{
private:
  pros::Motor liftMotor;

public:
  Lift(int liftPort);
  void init();
  void raiseArm(int pos);
  void lowerArm(int pos);
  void driverControl();
  void deploy();
};

#endif