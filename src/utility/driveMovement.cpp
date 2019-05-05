#include "main.h"

const int DRIVE_MOVEMENT_LINE = 1;
const int DRIVE_MOVEMENT_TURN = 2;

DriveMovement::DriveMovement(double angle)
{
  movementType = DRIVE_MOVEMENT_TURN;
  targetAngle = angle;
  speedDeadband = 1700;
  kp = 13;
}

double DriveMovement::getTargetAngle()
{
  return targetAngle;
}

int DriveMovement::getMovementType()
{
  return movementType;
}

int DriveMovement::getSpeedDeadband()
{
  return speedDeadband;
}

double DriveMovement::getKP()
{
  return kp;
}

void DriveMovement::setSpeedDeadband(int deadband)
{
  speedDeadband = deadband;
}

void DriveMovement::setKP(double value)
{
  kp = value;
}