#ifndef _LIFT_HPP_
#define _LIFT_HPP_

extern const int LIFT_MIDDLE_TOWER_POS;
extern const int LIFT_HIGH_TOWER_POS;

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
  void holdLiftDown();
};

#endif