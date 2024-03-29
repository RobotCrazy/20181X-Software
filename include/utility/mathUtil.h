#include "angle.hpp"

#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_

extern const double PI;

extern double degreeToRadian(double degrees);
extern double radianToDegree(double radians);
extern double distance(double x1, double y1, double x2, double y2);
extern bool isBetween(float number, float rangeLower, float rangeUpper);
extern double sign(double num);
extern double minDouble(double num1, double num2);
extern double maxDouble(double num1, double num2);

extern double angleQuadrantAdjustment(double x, double y);
extern double calculateShortestAngleDiff(Angle a1, Angle a2);

#endif