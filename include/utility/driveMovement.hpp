#include "api.h"
#include <vector>

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

  double targetX;
  double targetY;

  bool actionComplete = false;

  std::vector<DriveMovement> drivePrereqs;

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

  void addDrivePrereq(DriveMovement &dm);

  bool readyToOperate();
};

#endif