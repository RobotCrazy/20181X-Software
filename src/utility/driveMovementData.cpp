#include "main.h"
#include "utility/driveMovementData.hpp"

DriveMovementData::DriveMovementData(DriveMovement dm, double currentX, double currentY)
{
  driveMovement = dm;
  currentX = chassis.currentX;
  currentY = chassis.currentY;
  if (driveMovement.getMovementType() == DRIVE_MOVEMENT_POINT)
  {
    calculateTargetAngle();
  }
}

void DriveMovementData::calculateTargetAngle()
{
  targetAngle.setAngle(atan2(driveMovement.getTargetX() - currentX, driveMovement.getTargetY() - currentY));
}