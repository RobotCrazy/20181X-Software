#include "api.h"

#ifndef _TRAYTILTER_HPP_
#define _TRAYTILTER_HPP_ ;

class TrayTilter
{

private:
  pros::Motor tilter;

public:
  static const int DEPLOYED_POSITION = 720;

  TrayTilter(int tilterPort);
  void driverControl();
  int getPosition();
  void deployCubesOP(pros::controller_digital_e_t button);
};

#endif