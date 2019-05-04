#include "api.h"

#ifndef _CHASSIS_H_
#define _CHASSIS_H_

class Chassis
{
private:
  double currentX;
  double currentY;
  double currentAngle;
  pros::Motor frontLeftDrive;
  pros::Motor backLeftDrive;
  pros::Motor frontRightDrive;
  pros::Motor backRightDrive;

public:
  // Chassis(int frontLeft, int backLeft, int frontRight, int backRight);
  Chassis(int frontLeft, int backLeft, int frontRight, int backRight);
  void sensorInit();
};

#endif