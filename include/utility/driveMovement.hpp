#include "api.h"

#ifndef _DRIVEMOVEMENT_HPP_
#define _DRIVEMOVEMENT_HPP_

extern const int DRIVE_MOVEMENT_LINE;
//Movement type for driving to a specified point

extern const int DRIVE_MOVEMENT_TURN;
//Movement type for turning to a target angle

class DriveMovement
{
private:
  int movementType;
  int targetAngle;
  int speedDeadband;
  double kp;

public:
  DriveMovement(double targetAngle);
  DriveMovement(double x, double y, double targetAngle);

  double getTargetAngle();

  int getMovementType();
  int getSpeedDeadband();
  double getKP();

  void setSpeedDeadband(int deadband);
  void setKP(double value);
};

#endif