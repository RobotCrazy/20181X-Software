#ifndef _LIFT_HPP_
#define _LIFT_HPP_

class Lift
{
private:
  pros::Motor liftMotor;
  pros::ADIAnalogIn liftPot;

public:
  static const int LOW_TOWER_POS = 643;
  static const int MID_TOWER_POS = 962;
  int towerButtonCount;

  Lift(int liftPort, char liftPotPort);
  void init();
  void raiseArm(int pos);
  void lowerArm(int pos);
  void driverControl();
  void deploy();
};

#endif