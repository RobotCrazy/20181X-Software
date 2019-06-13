#include "api.h"
#include <vector>

#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

class Intake
{
private:
  pros::Motor intake;
  //std::vector<Movement> movements;

public:
  Intake(int intakePort);
  void driverControl();
};

#endif