#include "api.h"
#include "driveMovement.hpp"
#include "angle.hpp"

#ifndef _DRIVE_MOVEMENT_DATA_HPP_
#define _DRIVE_MOVEMENT_DATA_HPP_
class DriveMovementData
{
private:
  DriveMovement driveMovement;
  Angle targetAngle;
  double distanceToPoint;
  double currentX;
  double currentY;

  DriveMovementData(DriveMovement dm, double currentX, double currentY);
  void calculateTargetAngle();
};
#endif