#include "mathUtil.h"
#include <cmath>

const double PI = atan(1) * 4.0;

double degreeToRadian(double degrees)
{
  return degrees * (PI / 180.0);
}

double distance(double x1, double y1, double x2, double y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isBetween(float number, float rangeLower, float rangeUpper)
{
  return (number > rangeLower && number < rangeUpper);
}

double sign(double num)
{
  if (num > 0)
  {
    return 1;
  }
  else if (num < 0)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}