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
  if (voltage == 0)
  {
    frontRightDrive.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
    backRightDrive.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
  }
}

void Chassis::moveLeftDriveVoltage(int voltage)
{
  frontLeftDrive.move_voltage(voltage);
  backLeftDrive.move_voltage(voltage);
  if (voltage == 0)
  {
    frontLeftDrive.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
    backLeftDrive.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
  }
}

void Chassis::addMovement(DriveMovement &dm)
{
  //movements.push_back(dm);
}

void Chassis::driverControl()
{
  moveRightDrive(master.get_analog(ANALOG_LEFT_Y));
  moveLeftDrive(master.get_analog(ANALOG_RIGHT_Y));
}

void Chassis::deleteFirstMovement()
{
  /*movements.at(0).setComplete();
  movements.erase(movements.begin());*/
}

void Chassis::completeMovements()
{
  /*if (movements.size() > 0)
  {
    DriveMovement dm = movements.at(0);

    if (dm.getMovementType() == DRIVE_MOVEMENT_TURN)
    {
      if (turnToTarget(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP()) == true)
      {

        deleteFirstMovement();
      }
    }
    else if (dm.getMovementType() == DRIVE_MOVEMENT_LINE)
    {
      if (driveToPoint(dm.getTargetX(), dm.getTargetY(), dm.getSpeedDeadband(),
                       dm.getKP()) == true)
      {
        deleteFirstMovement();
      }
    }
  }*/
}

void Chassis::sensorInit()
{
  //reset encoders, gyros, etc for drive base here
}

bool Chassis::driveToPoint(double x, double y, int speedDeadband, int kp)
{
  //Insert code for driving to a point with odometry here
  //This code should dynamically update its path if external factors cause the robot to
  //get off course.
  // Look at motion profiling concepts for this
}

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, int kp)
{

  //This function is still missing shortest path addition to choose which direction
  //is the quickest to reach desired angle

  float scaledAngle = targetAngle * GYRO_SCALE;
  const int tolerance = 5;
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