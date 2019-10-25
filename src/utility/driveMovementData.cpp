// #include "main.h"
// #include "utility/driveMovementData.hpp"

// DriveMovementData::DriveMovementData(DriveMovement dm, double currentX, double currentY)
// {
//   driveMovement = dm;
//   currentX = chassis.currentX;
//   currentY = chassis.currentY;
//   if (driveMovement.getMovementType() == DRIVE_MOVEMENT_POINT)
//   {
//     calculateTargetAngle();
//     currentPhase = TURN_PHASE;
//   }
// }

// Angle DriveMovementData::getTargetAngle()
// {
//   return targetAngle;
// }

// void DriveMovementData::calculateTargetAngle()
// {
//   targetAngle.setAngle(atan2(driveMovement.getTargetX() - currentX, driveMovement.getTargetY() - currentY));
// }

// int DriveMovementData::getPhase()
// {
//   return currentPhase;
// }

// void DriveMovementData::setPhase(int phase)
// {
//   currentPhase = phase;
// }