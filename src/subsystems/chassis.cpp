#include "main.h"

Chassis::Chassis(int frontLeft, int backLeft, int frontRight, int backRight)
    : frontLeftDrive(frontLeft), backLeftDrive(backLeft), frontRightDrive(frontRight),
      backRightDrive(backRight)
{
  sensorInit();
}

void Chassis::sensorInit()
{
  //reset encoders, gyros, etc for drive base here
}