#include "main.h"
#include "movement.hpp"
#include <vector>

const int DRIVE_MOVEMENT_POINT = 1;
const int DRIVE_MOVEMENT_TURN = 2;

const double DriveMovement::TURN_DEFAULT_SPEED_DEADBAND = 2500.0;
const double DriveMovement::TURN_DEFAULT_MAX_SPEED = 12000.0;
const double DriveMovement::TURN_DEFAULT_KP = 8000.0;
const bool DriveMovement::TURN_DEFAULT_COMPLETION_STOP = true;

DriveMovement::DriveMovement()
{
}

DriveMovement::DriveMovement(double angle)
{
  movementType = DRIVE_MOVEMENT_TURN;
  targetAngle = angle;
  speedDeadband = TURN_DEFAULT_SPEED_DEADBAND;
  maxSpeed = TURN_DEFAULT_MAX_SPEED;
  kp = TURN_DEFAULT_KP;
  stopOnCompletion = TURN_DEFAULT_COMPLETION_STOP;
  prereqMovements = std::vector<std::shared_ptr<Movement>>({});
  //The values for speedDeadband and KP in this constructor are the default values.
  //These can be set using seperate methods for specific cases.
}

DriveMovement::DriveMovement(double x, double y)
{
  movementType = DRIVE_MOVEMENT_POINT;
  targetX = x;
  targetY = y;
  speedDeadband = 3000;
  maxSpeed = 12000;
  kp = 400.0;
  stopOnCompletion = true;
}

double DriveMovement::getTargetAngle()
{
  return targetAngle;
}

void DriveMovement::setTargetAngle(double newAngle)
{
  targetAngle = newAngle;
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

void DriveMovement::setDrivePrereq(std::shared_ptr<Prereq> p)
{
  drivePrereq = p;
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