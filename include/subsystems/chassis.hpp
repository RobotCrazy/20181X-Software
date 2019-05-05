#include "api.h"
#include <vector>
#include "utility/driveMovement.hpp"

#ifndef _CHASSIS_HPP_
#define _CHASSIS_HPP_

#define WHEEL_RADIUS 2
#define WHEEL_CIRCUMFERENCE WHEEL_RADIUS * 2 * PI
#define GYRO_SCALE .78

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
  pros::ADIGyro gyro;

  std::vector<DriveMovement> movements;

public:
  Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort);
  void moveRightDrive(int value);
  void moveLeftDrive(int value);
  void moveRightDriveVoltage(int voltage);
  void moveLeftDriveVoltage(int voltage);

  void driverControl();
  void completeMovements();
  void sensorInit();

  bool turnToTarget(double targetAngle, int speedDeadband, int kp);
};

#endif