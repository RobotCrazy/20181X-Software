#include "api.h"

#ifndef _TRAYTILTER_HPP_
#define _TRAYTILTER_HPP_ ;

class TrayTilter
{

private:
  pros::Motor tilter;
  pros::ADIAnalogIn tilterPot;
  int targetPos;

public:
  static const int DEPLOYED_POSITION = 3850;

  bool moveTilterRequested;

  TrayTilter(int tilterPort, char tilterPotPort);
  void init();
  void driverControl();
  int getPosition();
  void move(int speed);
  void deployCubes();
  void deployCubesOP();
  void setTargetPos(int target);
  void moveToTargetPos();
  void moveTrayAt(int speed);
};

#endif