#include "main.h"
#include "angle.hpp"
#include "utility/mathUtil.h"

Angle::Angle(double a)
{
  angle = determinePositiveEquivalent(a);
}

double Angle::determinePositiveEquivalent(double a)
{
  //write code to determine positive equivalent
  //Ex: -PI/2 -> 3PI/2
}
double Angle::getAngle()
{
  return angle;
}

double Angle::getAngleDegrees()
{
  return radianToDegree(angle);
}