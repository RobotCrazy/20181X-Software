#include "api.h"

#ifndef _ANGLE_HPP_
#define _ANGLE_HPP_

class Angle
{

private:
  double angle;

public:
  Angle();
  Angle(double a);
  double determinePositiveEquivalent(double a);
  double getAngle();
  double getAngleDegrees();
  void setAngle(double a);
};
#endif