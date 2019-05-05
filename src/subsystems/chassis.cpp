#include "main.h"

Chassis::Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort)
    : frontLeftDrive(frontLeft), backLeftDrive(backLeft), frontRightDrive(frontRight),
      backRightDrive(backRight), gyro(gyroPort)
{
  sensorInit();
}

void Chassis::moveRightDrive(int value)
{
  frontRightDrive.move(value);
  backRightDrive.move(value);
}

void Chassis::moveLeftDrive(int value)
{
  frontLeftDrive.move(value);
  backLeftDrive.move(value);
}

void Chassis::moveRightDriveVoltage(int voltage)
{
  frontRightDrive.move_voltage(voltage);
  backRightDrive.move_voltage(voltage);
}

void Chassis::moveLeftDriveVoltage(int voltage)
{
  frontLeftDrive.move_voltage(voltage);
  backLeftDrive.move_voltage(voltage);
}

void Chassis::driverControl()
{
  moveRightDrive(master.get_analog(ANALOG_LEFT_Y));
  moveLeftDrive(master.get_analog(ANALOG_RIGHT_Y));
}

void Chassis::completeMovements()
{
  if (movements.size() > 0)
  {
    DriveMovement dm = movements.at(0);

    if (dm.getMovementType() == DRIVE_MOVEMENT_TURN)
    {
      if (turnToTarget(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP()) == true)
      {
        movements.erase(movements.begin());
      }
    }
  }
}

void Chassis::sensorInit()
{
  //reset encoders, gyros, etc for drive base here
}

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, int kp)
{
  int tolerance = 5;
  float scaledAngle = targetAngle * GYRO_SCALE;
  int error = (scaledAngle * 10.0) - gyro.get_value();
  int driveSpeed = error * kp;

  if (abs(error) > tolerance)
  {
    error = (scaledAngle * 10) - gyro.get_value();
    driveSpeed = error * kp;

    if (isBetween(driveSpeed, -1 * speedDeadband, 0))
    {
      driveSpeed = -1 * speedDeadband;
    }
    if (isBetween(driveSpeed, 0, speedDeadband))
    {
      driveSpeed = speedDeadband;
    }

    moveRightDriveVoltage(driveSpeed * -1);
    moveLeftDriveVoltage(driveSpeed);
    return false;
  }
  else
  {
    return true;
  }
}