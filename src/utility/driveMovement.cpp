#include "main.h"

const int DRIVE_MOVEMENT_POINT = 1;
const int DRIVE_MOVEMENT_TURN = 2;

DriveMovement::DriveMovement(double angle)
{
  movementType = DRIVE_MOVEMENT_TURN;
  targetAngle = angle;
  speedDeadband = 1700;
  maxSpeed = 12000;
  kp = 5000.0;
  stopOnCompletion = true;
  //The values for speedDeadband and KP in this constructor are the default values.
  //These can be set using seperate methods for specific cases.
}

DriveMovement::DriveMovement(double x, double y)
{
  movementType = DRIVE_MOVEMENT_POINT;
  targetX = x;
  targetY = y;
  speedDeadband = 1700;
  maxSpeed = 12000;
  kp = 13;
  stopOnCompletion = true;
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

double DriveMovement::getTargetX()
{
  return targetX;
}
double DriveMovement::getTargetY()
{
  return targetY;
}

void DriveMovement::setSpeedDeadband(int deadband)
{
  speedDeadband = deadband;
}

void DriveMovement::setKP(double value)
{
  kp = value;
}

void DriveMovement::setComplete()
{
  actionComplete = true;
}

bool DriveMovement::isComplete()
{
  return actionComplete;
}

void DriveMovement::setDrivePrereq(Prereq p)
{
  drivePrereq = p;
}

bool DriveMovement::readyToOperate()
{
  return drivePrereq.isComplete();
}

void DriveMovement::setStopOnCompletion(bool stop)
{
  stopOnCompletion = stop;
}

bool DriveMovement::getStopOnCompletion()
{
  return stopOnCompletion;
}

void DriveMovement::setMaxSpeed(int voltage)
{
  maxSpeed = voltage;
}

int DriveMovement::getMaxSpeed()
{
  return maxSpeed;
}

/*void DriveMovement::addIntakePrereq(IntakeMovement im)
{
  intakePreqs.push_back(im)
}*/