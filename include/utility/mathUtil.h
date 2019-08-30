#ifndef _MATHUTIL_H_
#define _MATHUTIL_H_

extern const double PI;

extern double degreeToRadian(double degrees);
extern double distance(double x1, double y1, double x2, double y2);
extern bool isBetween(float number, float rangeLower, float rangeUpper);
extern double sign(double num);

extern double angleQuadrantAdjustment(double x, double y);

#endif