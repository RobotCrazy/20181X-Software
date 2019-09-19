#include "api.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <memory>
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
  pros::ADIGyro gyro;

  std::queue<DriveMovement *> movements;
  std::queue<std::shared_ptr<DriveMovement>> ms;
  std::vector<DriveMovement *> completedMovements;

public:
  Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort);
  pros::Motor frontLeftDrive;
  pros::Motor backLeftDrive;
  pros::Motor frontRightDrive;
  pros::Motor backRightDrive;
  double currentX = 0;
  double currentY = 0;
  double currentAngle = (PI / 2.0);
  void moveRightDrive(int value);
  void moveLeftDrive(int value);
  void driverControl();
  void moveRightDriveVoltage(int voltage);
  void moveLeftDriveVoltage(int voltage);

  void setCurrentAngle(double angle);
  void printCoords();
  void addMovement(DriveMovement *dm);
  bool movementIsCompleted(DriveMovement *dm);
  DriveMovement *getFirstMovement();
  void deleteFirstMovement();
  void completeMovements();
  void initialize();
  void sensorInit();

  void trackPosition();

  /**
   * Drives to a specified point
   * Returns whether the action is complete (true if complete; false otherwise)
   */
  bool driveToPoint(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion);
  bool driveToPointSync(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion);
  bool turnToTarget(double targetAngle, int speedDeadband, double kp, bool stopOnCompletion);
};

extern void chassisTaskActions(void *param);
extern pros::Task chassisControl;

#endif