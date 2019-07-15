#include "api.h"
#include <vector>
#include "prereq.hpp"

#ifndef _DRIVEMOVEMENT_HPP_
#define _DRIVEMOVEMENT_HPP_

extern const int DRIVE_MOVEMENT_POINT;
//Movement type for driving to a specified point

extern const int DRIVE_MOVEMENT_TURN;
//Movement type for turning to a target angle

class DriveMovement
{
private:
  int movementType;
  double targetAngle;
  int speedDeadband;
  int maxSpeed;
  double kp;

  double targetX;
  double targetY;

  bool actionComplete = false;
  bool stopOnCompletion;

  Prereq drivePrereq;

public:
  DriveMovement(double targetAngle);
  DriveMovement(double x, double y);

  double getTargetAngle();

  int getMovementType();
  int getSpeedDeadband();
  double getKP();

  double getTargetX();
  double getTargetY();

  void setSpeedDeadband(int deadband);
  void setKP(double value);

  void setComplete();
  bool isComplete();

  void setDrivePrereq(Prereq p);

  bool readyToOperate();

  void setStopOnCompletion(bool stop);
  bool getStopOnCompletion();

  void setMaxSpeed(int voltage);
  int getMaxSpeed();
};

#endif