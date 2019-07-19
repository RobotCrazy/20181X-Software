#include "main.h"
#include "utility/mathUtil.h"

const double WHEEL_RADIUS = 2.0;
const double WHEEL_CIRCUMFERENCE = WHEEL_RADIUS * 2.0 * PI;
const double GYRO_SCALE = .78;
const double leftTWheelDistance = 6.0;
const double rightTWheelDistance = 6.0;
const double DRIVE_BASE_GEARING = 1.25;
double prevFRDrive = 0;
double prevBRDrive = 0;
double prevFLDrive = 0;
double prevBLDrive = 0;

Chassis::Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort)
    : frontLeftDrive(frontLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backLeftDrive(backLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      frontRightDrive(frontRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backRightDrive(backRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      gyro(gyroPort)
{
  sensorInit();
  initialize();
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
  frontRightDrive.move_voltage(voltage * -1);
  backRightDrive.move_voltage(voltage * -1);
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

void Chassis::printCoords()
{
  pros::lcd::print(3, "%f", currentX);
  pros::lcd::print(4, "%f", currentY);
  pros::lcd::print(5, "%f", currentAngle);
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
    //pros::lcd::print(6, "Inside if statement");
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

void Chassis::initialize()
{
  currentX = 0.0;
  currentY = 0.0;
  currentAngle = PI / 2;
  pros::lcd::print(7, "initing %f", currentX);
}

void Chassis::sensorInit()
{
  frontRightDrive.tare_position();
  backRightDrive.tare_position();
  frontLeftDrive.tare_position();
  backLeftDrive.tare_position();
  currentX = 0.0;
  currentY = 0.0;
  currentAngle = PI / 2;
  //reset encoders, gyros, etc for drive base here
}

void Chassis::trackPosition()
{
  //current angle will start at 90 degrees or PI/2 radians

  double frDrive = degreeToRadian(frontRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  double brDrive = degreeToRadian(backRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  double flDrive = degreeToRadian(frontLeftDrive.get_position()) * DRIVE_BASE_GEARING;
  double blDrive = degreeToRadian(backLeftDrive.get_position()) * DRIVE_BASE_GEARING;

  // float rightEncAverage = ((frDrive - prevFRDrive) +
  //                          (brDrive - prevBRDrive)) /
  //                         2;
  // float leftEncAverage = ((flDrive - prevFLDrive) +
  //                         (blDrive - prevBLDrive)) /
  //                        2;
  double frDriveInches = (frDrive - prevFRDrive) * WHEEL_RADIUS;
  double flDriveInches = (flDrive - prevFLDrive) * WHEEL_RADIUS;

  double angleChange = (flDriveInches - frDriveInches) / (leftTWheelDistance + rightTWheelDistance);
  currentAngle += angleChange;
  //The problem with the angle change may be that the drive is geared.  We need to scale everything
  //by the gearing to make sure the motor's encoder readings are correct.  We should scale the ticks
  //that the encoders read by (I think 1.25)

  double traveledDistanceR = 0;
  double traveledDistanceL = 0;
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
  double xTranslationR = cos(currentAngle) * traveledDistanceR;
  double yTranslationR = sin(currentAngle) * traveledDistanceR;

  double xTranslationL = cos(currentAngle) * traveledDistanceL;
  double yTranslationL = sin(currentAngle) * traveledDistanceL;

  double finalXTranslation = (xTranslationR + xTranslationL) / 2.0;
  double finalYTranslation = (yTranslationR + yTranslationL) / 2.0;

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

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, double kp, bool stopOnCompletion)
{

  //This function is still missing shortest path addition to choose which direction
  //is the quickest to reach desired angle

  const double tolerance = .05;
  /*if (abs(targetAngle - currentAngle) > abs((targetAngle + ((targetAngle > 0) ? (-2 * PI) : (2 * PI)) - currentAngle)))
  {
    targetAngle = ((targetAngle > 0) ? (-2 * PI) : (2 * PI));
  } //find shortest direction to target angle*/
  double error = targetAngle - currentAngle;
  double driveSpeed = error * kp;
  pros::lcd::print(3, "%f", driveSpeed);
  pros::lcd::print(4, "%f", currentAngle);
  pros::lcd::print(5, "%f", fabs(error));

  if (fabs(error) > tolerance)
  {
    error = targetAngle - currentAngle;
    driveSpeed = error * kp;

    if (abs(driveSpeed) < speedDeadband)
    {
      driveSpeed = speedDeadband * sign(driveSpeed);
    }

    moveRightDriveVoltage(driveSpeed * -1.0);
    moveLeftDriveVoltage(driveSpeed);

    return false;
  }
  else
  {
    moveRightDriveVoltage(0);
    moveLeftDriveVoltage(0);
    return true;
  }
}

/*
This function invokes all actions that belong to the chassis subsytem that need to be iterated over.  
 */
void chassisTaskActions(void *param)
{

  int i = 0;
  while (true)
  {
    if (i == 0)
    {
      chassis.sensorInit();
    }

    //pros::lcd::print(7, "%d", pros::Task::get_count());
    chassis.trackPosition();

    chassis.printCoords();
    //chassis.completeMovements();
    pros::lcd::print(6, "Task %d", i);
    i++;
    pros::delay(10);
  }
}

/*void chassisAutonActions(void *param)
{
  while (true)
  {
    chassis.completeMovements();
    //pros::lcd::print(4, "Running auton actions");

    pros::delay(10);
  }
}
*/

pros::Task chassisControl(chassisTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Subsystem Task");