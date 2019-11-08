#include "api.h"
#include <vector>
#include <memory>
#include "prereq.hpp"
#include "angle.hpp"
#include "movement.hpp"

#ifndef _DRIVEMOVEMENT_HPP_
#define _DRIVEMOVEMENT_HPP_

extern const int DRIVE_MOVEMENT_POINT;
//Movement type for driving to a specified point

extern const int DRIVE_MOVEMENT_TURN;
//Movement type for turning to a target angle

class DriveMovement : public Movement
{
private:
  int movementType;
  double targetAngle;
  int speedDeadband;
  int maxSpeed;
  double kp;

  double targetX;
  double targetY;

  bool stopOnCompletion;

  std::shared_ptr<Prereq> drivePrereq;

  Angle targAngle;

public:
  static const double TURN_DEFAULT_SPEED_DEADBAND;
  static const double TURN_DEFAULT_MAX_SPEED;
  static const double TURN_DEFAULT_KP;
  static const bool TURN_DEFAULT_COMPLETION_STOP;

  bool turnTargetAngleIsSet = false;

  DriveMovement();
  DriveMovement(double targetAngle);
  DriveMovement(double x, double y);

  double getTargetAngle();
  void setTargetAngle(double newAngle);

  int getMovementType();
  int getSpeedDeadband();
  double getKP();

  double getTargetX();
  double getTargetY();

  void setSpeedDeadband(int deadband);
  void setKP(double value);

  void setDrivePrereq(std::shared_ptr<Prereq> p);

  void setStopOnCompletion(bool stop);
  bool getStopOnCompletion();

  void setMaxSpeed(int voltage);
  int getMaxSpeed();
};

#endif