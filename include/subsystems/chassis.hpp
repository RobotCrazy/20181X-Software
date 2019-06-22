#include "api.h"
#include <queue>
#include "../utility/driveMovement.hpp"
#include "../utility/prereq.hpp"
#include "../utility/mathUtil.h"

#ifndef _CHASSIS_HPP_
#define _CHASSIS_HPP_

extern const double WHEEL_RADIUS;
extern const double WHEEL_CIRCUMFERENCE;
extern const double GYRO_SCALE;
extern const double leftTWheelDistance;
extern const double rightTWheelDistance;

extern pros::Task chassisControl;

class Chassis
{
private:
  double currentX = 0;
  double currentY = 0;
  double currentAngle = (PI / 2);
  pros::Motor frontLeftDrive;
  pros::Motor backLeftDrive;
  pros::Motor frontRightDrive;
  pros::Motor backRightDrive;
  pros::ADIGyro gyro;

  std::queue<DriveMovement> movements;

public:
  Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort);
  void moveRightDrive(int value);
  void moveLeftDrive(int value);
  void driverControl();
  void moveRightDriveVoltage(int voltage);
  void moveLeftDriveVoltage(int voltage);

  void addMovement(DriveMovement dm);
  DriveMovement getFirstMovement();
  void deleteFirstMovement();
  void completeMovements();
  void sensorInit();

  void trackPosition();
  bool driveToPoint(double x, double y, int speedDeadband, int kp);
  bool turnToTarget(double targetAngle, int speedDeadband, int kp);
};

#endif