#include "main.h"

const double WHEEL_RADIUS = 2;
const double WHEEL_CIRCUMFERENCE = WHEEL_RADIUS * 2 * PI;
const double GYRO_SCALE = .78;
const double leftTWheelDistance = 6.1875;
const double rightTWheelDistance = 6.1875;
const double DRIVE_BASE_GEARING = 1.25;

Chassis::Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort)
    : frontLeftDrive(frontLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backLeftDrive(backLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      frontRightDrive(frontRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backRightDrive(backRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      gyro(gyroPort)
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

void Chassis::driverControl()
{
  moveLeftDrive(master.get_analog(ANALOG_LEFT_Y));
  moveRightDrive(master.get_analog(ANALOG_RIGHT_Y) * -1);
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

void Chassis::addMovement(DriveMovement dm)
{
  movements.push(dm);
}

DriveMovement Chassis::getFirstMovement()
{
  return movements.front();
}

void Chassis::deleteFirstMovement()
{
  movements.pop();
}

void Chassis::completeMovements()
{
  if (movements.empty() == false)
  {
    DriveMovement dm = getFirstMovement();
    if (dm.readyToOperate() == true)
    {
      if (dm.getMovementType() == DRIVE_MOVEMENT_TURN)
      {
        if (turnToTarget(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP(), dm.getStopOnCompletion()) == true)
        {
          deleteFirstMovement();
        }
      }
      else if (dm.getMovementType() == DRIVE_MOVEMENT_POINT)
      {
        if (driveToPoint(dm.getTargetX(), dm.getTargetY(), dm.getSpeedDeadband(), dm.getMaxSpeed(), dm.getKP(), dm.getStopOnCompletion()) == true)
        {
          deleteFirstMovement();
        }
      }
    }
  }
}

void Chassis::sensorInit()
{
  frontRightDrive.tare_position();
  backRightDrive.tare_position();
  frontLeftDrive.tare_position();
  backLeftDrive.tare_position();
  //reset encoders, gyros, etc for drive base here
}

float prevFRDrive = 0;
float prevBRDrive = 0;
float prevFLDrive = 0;
float prevBLDrive = 0;
void Chassis::trackPosition()
{
  //current angle will start at 90 degrees or PI/2 radians

  float frDrive = degreeToRadian(frontRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  float brDrive = degreeToRadian(backRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  float flDrive = degreeToRadian(frontLeftDrive.get_position()) * DRIVE_BASE_GEARING;
  float blDrive = degreeToRadian(backLeftDrive.get_position()) * DRIVE_BASE_GEARING;

  // float rightEncAverage = ((frDrive - prevFRDrive) +
  //                          (brDrive - prevBRDrive)) /
  //                         2;
  // float leftEncAverage = ((flDrive - prevFLDrive) +
  //                         (blDrive - prevBLDrive)) /
  //                        2;
  float frDriveInches = (frDrive - prevFRDrive) * WHEEL_RADIUS;
  float flDriveInches = (flDrive - prevFLDrive) * WHEEL_RADIUS;

  float angleChange = (flDriveInches - frDriveInches) / (leftTWheelDistance + rightTWheelDistance);
  currentAngle += angleChange;
  //The problem with the angle change may be that the drive is geared.  We need to scale everything
  //by the gearing to make sure the motor's encoder readings are correct.  We should scale the ticks
  //that the encoders read by (I think 1.25)

  float traveledDistanceR = 0;
  float traveledDistanceL = 0;
  if (angleChange == 0)
  {
    traveledDistanceR = frDriveInches;
    traveledDistanceL = flDriveInches;
  }
  else
  {
    traveledDistanceR = ((frDriveInches / angleChange) * sin(angleChange)) / sin((PI - angleChange) / 2.0);
    traveledDistanceL = ((flDriveInches / angleChange) * sin(angleChange)) / sin((PI - angleChange) / 2.0);
  }
  float xTranslationR = cos(currentAngle) * traveledDistanceR;
  float yTranslationR = sin(currentAngle) * traveledDistanceR;

  float xTranslationL = cos(currentAngle) * traveledDistanceL;
  float yTranslationL = sin(currentAngle) * traveledDistanceL;

  float finalXTranslation = (xTranslationR + xTranslationL) / 2.0;
  float finalYTranslation = (yTranslationR + yTranslationL) / 2.0;

  currentX += finalXTranslation;
  currentY += finalYTranslation;

  pros::lcd::print(0, "%f", currentX);
  pros::lcd::print(1, "%f", currentY);
  pros::lcd::print(2, "%f", currentAngle);

  prevFRDrive = frDrive;
  prevBRDrive = brDrive;
  prevFLDrive = flDrive;
  prevBLDrive = blDrive;
}

bool Chassis::driveToPoint(double x, double y, int speedDeadband, int maxSpeed, int kp, bool stopOnCompletion)
{
  const double angleThreshold = (PI / 6.0);
  const double angleKP = 1.0; //Tune these two constants as needed
  const double errorTolerance = .25;
  double xDistance = x - currentX;
  double yDistance = y - currentY;
  double targetAngle = atan(yDistance / xDistance);
  double error = distance(currentX, currentY, x, y);
  double speed = error * kp;
  if (abs(targetAngle - currentAngle) > angleThreshold)
  {
    turnToTarget(targetAngle, speedDeadband, kp, false);
    return false;
  }
  else
  {
    double angleDifference = currentAngle - targetAngle; //It might need to be flipped depending on
    //which angle is positive and which is negative (targetAngle - currentAngle)
    moveRightDriveVoltage((error * kp) + (angleDifference * angleKP));
    moveLeftDriveVoltage((error * kp) - (angleDifference * angleKP)); //It might need to be
    //addition instead of subtraction or vice versa
  }
  return (abs(error) < errorTolerance);

  //Insert code for driving to a point with odometry here
  //This code should dynamically update its path if external factors cause the robot to
  //get off course.
  // Look at motion profiling concepts for this
}

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, int kp, bool stopOnCompletion)
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

/*
This function invokes all actions that belong to the chassis subsytem that need to be iterated over.  
 */
void chassisTaskActions(void *param)
{
  while (true)
  {
    chassis.trackPosition();
    chassis.completeMovements();

    pros::delay(10);
  }
}

pros::Task chassisControl(chassisTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Subsystem Task");