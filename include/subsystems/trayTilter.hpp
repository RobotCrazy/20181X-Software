#include "api.h"

#ifndef _TRAYTILTER_HPP_
#define _TRAYTILTER_HPP_ ;

class TrayTilter
{

private:
  pros::Motor tilter;
  int targetPos;

public:
  static const int DEPLOYED_POSITION = 2520;

  bool moveTilterRequested;

  TrayTilter(int tilterPort);
  void init();
  void driverControl();
  int getPosition();
  void move(int speed);
  void deployCubes();
  void deployCubesOP(pros::controller_digital_e_t button);
  void setTargetPos(int target);
  void moveToTargetPos();
};

#endif