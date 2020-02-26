#include "api.h"
#include <queue>
#include <list>
#include <algorithm>
#include <memory>
#include "../utility/driveMovement.hpp"
#include "../utility/prereq.hpp"
#include "../utility/mathUtil.h"
#include "../utility/angle.hpp"

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
  int globalTargetAngle;

  std::queue<std::shared_ptr<DriveMovement>> movements;
  std::list<std::shared_ptr<DriveMovement>> completedMovements;

public:
  Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort);
  pros::Motor frontLeftDrive;
  pros::Motor backLeftDrive;
  pros::Motor frontRightDrive;
  pros::Motor backRightDrive;
  pros::ADIGyro gyro;
  double currentX = 0;
  double currentY = 0;
  Angle currentAngle;
  void moveRightDrive(int value);
  void moveLeftDrive(int value);
  void driverControl();
  void moveRightDriveVoltage(int voltage);
  void moveLeftDriveVoltage(int voltage);

  void setGlobalTargetAngle(int newAngle);
  void setCurrentAngle(double angle);
  void printCoords();
  
  double getRightSideVelocity();
  double getLeftSideVelocity();

  /**
   * Adds movement to queue of chassis actions
   * Param dm - shared_ptr to DriveMovement object
   */
  void addMovement(std::shared_ptr<DriveMovement> dm);

  bool movementIsCompleted(DriveMovement *dm);

  /**
   * Returns shared_ptr to first movement in queue of chassis actions
   */
  std::shared_ptr<DriveMovement> getFirstMovement();

  /**
   * Deletes first movement in queue of chassis actions
   */
  void deleteFirstMovement();

  /**
   * Completes work to complete actions in chassis actions queue
   */
  void completeMovements();
  void initialize();
  void sensorInit();

  /**
  * Keeps track of absolute robot position
  */
  void trackPosition();

  /**
   * Drives to a specified point
   * Returns whether the action is complete (true if complete; false otherwise)
   */
  bool driveToPoint(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion);

  void driveToPointSync(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion);

  void driveBackward(double inches, int speedDeadband, int maxSpeed);

  void driveBackward(double inches, int speedDeadband, int maxSpeed, pros::controller_digital_e_t);

  void driveRampUp(char dir, float inches, float increaseFactor = 18, int maxSpeed = 12000);

  void applyBrakeForDrive(int power, int speedTolerance);

  /**
   * Turns to a specified angle
   * Returns whether the action is complete (true of complete; false otherwise)
   */
  void turnToTarget(float targetAngle, int maxSpeed = 12000);

  float getRotationalVelocity();

  void applyBrakeForTurn(int leftPower, int rightPower, int speedTolerance);

  void turnToTargetSync(Angle targetAngle, int speedDeadband, double kp, bool stopOnCompletion);

  void waitUntilSettled();
};

extern void chassisTaskActions(void *param);
extern pros::Task chassisControl;

#endif