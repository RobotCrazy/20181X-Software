#include "main.h"
#include "angle.hpp"
#include <functional>
#include "utility/mathUtil.h"

Angle::Angle() {}

Angle::Angle(double a)
{
  angle = determinePositiveEquivalent(a);
}

double Angle::determinePositiveEquivalent(double a)
{
  //write code to determine positive equivalent
  //Ex: -PI/2 -> 3PI/2
  double angleValue = fmod(a, (2.0 * PI));
  if (angleValue < 0)
  {
    angleValue + (2.0 * PI);
  }
  return angleValue;
}

double Angle::getAngle()
{
  return angle;
}

double Angle::getAngleDegrees()
{
  return radianToDegree(angle);
}

void Angle::setAngle(double a)
{
  angle = determinePositiveEquivalent(a);
}