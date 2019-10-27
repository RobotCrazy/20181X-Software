#include "main.h"
#include "utility/mathUtil.h"
#include "utility/angle.hpp"

Logger l("/usd/chassisLog.txt");
Logger errorlogger("/usd/errorLog.txt");
Logger targetAngleLogger("/usd/targetAngleLog.txt");
Logger angleDifferenceLogger("/usd/angleDifferenceLog.txt");

const double WHEEL_RADIUS = 2.0;
const double WHEEL_CIRCUMFERENCE = WHEEL_RADIUS * 2.0 * PI;
const double GYRO_SCALE = .78;
const double leftTWheelDistance = 6.0;
const double rightTWheelDistance = 6.0;
const double DRIVE_BASE_GEARING = 1.25;
double prevFRDrive = degreeToRadian(chassis.frontRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
double prevBRDrive = degreeToRadian(chassis.backRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
double prevFLDrive = degreeToRadian(chassis.frontLeftDrive.get_position()) * DRIVE_BASE_GEARING;
double prevBLDrive = degreeToRadian(chassis.backLeftDrive.get_position()) * DRIVE_BASE_GEARING;

Chassis::Chassis(int frontLeft, int backLeft, int frontRight, int backRight, char gyroPort)
    : frontLeftDrive(frontLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backLeftDrive(backLeft, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      frontRightDrive(frontRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      backRightDrive(backRight, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES),
      gyro(gyroPort), currentAngle(PI / 2.0)
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

void Chassis::setCurrentAngle(double angle)
{
  currentAngle.setAngle(angle);
}

void Chassis::printCoords()
{
}

void Chassis::addMovement(std::shared_ptr<DriveMovement> dm)
{
  movements.push(dm);
}

bool Chassis::movementIsCompleted(DriveMovement *dm)
{
  return false; //(std::find(completedMovements.begin(), completedMovements.end(), dm) != completedMovements.end());
}

std::shared_ptr<DriveMovement> Chassis::getFirstMovement()
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
    std::shared_ptr<DriveMovement> dmPointer = getFirstMovement();
    DriveMovement dm = *(dmPointer.get());
    //pros::lcd::print(4, "Point: (%f, %f) %d", dm.getTargetX(), dm.getTargetY(), movements.size());
    //pros::lcd::print(5, "%d", dm->getMovementType());
    if (dm.readyToOperate() == true)
    {
      if (dm.getMovementType() == DRIVE_MOVEMENT_POINT)
      {
        driveToPointSync(dm.getTargetX(), dm.getTargetY(), dm.getSpeedDeadband(), dm.getMaxSpeed(), dm.getKP(), dm.getStopOnCompletion());
        completedMovements.push_back(dmPointer);
        deleteFirstMovement();
        pros::lcd::print(5, "Deleting movement");

        // if (driveToPoint(dm.getTargetX(), dm.getTargetY(), dm.getSpeedDeadband(), dm.getMaxSpeed(), dm.getKP(), dm.getStopOnCompletion()) == true)
        // {
        //   dmPointer.get()->setComplete();
        //   completedMovements.push_back(dmPointer);
        //   deleteFirstMovement();
        //   pros::lcd::print(5, "Deleting movement");
        // }
      }

      else if (dm.getMovementType() == DRIVE_MOVEMENT_TURN)
      {

        turnToTargetSync(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP(), dm.getStopOnCompletion());
        dmPointer.get()->setComplete();
        completedMovements.push_back(dmPointer);
        deleteFirstMovement();
        pros::lcd::print(5, "Deleting movement");

        // if (turnToTarget(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP(), dm.getStopOnCompletion()) == true)
        // {
        //   dmPointer.get()->setComplete();
        //   completedMovements.push_back(dmPointer);
        //   deleteFirstMovement();
        //   pros::lcd::print(5, "Deleting movement");
        // }
      }
    }
  }
}

void Chassis::initialize()
{
  currentX = 0.0;
  currentY = 0.0;
  currentAngle.setAngle(PI / 2);
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
  currentAngle.setAngle(PI / 2.0);
  //pros::delay(200);

  //reset encoders, gyros, etc for drive base here
}

void Chassis::trackPosition()
{
  //current angle will start at 90 degrees or PI/2 radians

  double frDrive = 0;
  frDrive = degreeToRadian(frontRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  double brDrive = 0;
  brDrive = degreeToRadian(backRightDrive.get_position() * -1) * DRIVE_BASE_GEARING;
  double flDrive = 0;
  flDrive = degreeToRadian(frontLeftDrive.get_position()) * DRIVE_BASE_GEARING;
  double blDrive = 0;
  blDrive = degreeToRadian(backLeftDrive.get_position()) * DRIVE_BASE_GEARING;

  // float rightEncAverage = ((frDrive - prevFRDrive) +
  //                          (brDrive - prevBRDrive)) /
  //                         2;
  // float leftEncAverage = ((flDrive - prevFLDrive) +
  //                         (blDrive - prevBLDrive)) /
  //                        2;
  double frDriveInches = (frDrive - prevFRDrive) * WHEEL_RADIUS;
  double flDriveInches = (flDrive - prevFLDrive) * WHEEL_RADIUS;

  double angleChange = (flDriveInches - frDriveInches) / (leftTWheelDistance + rightTWheelDistance);
  currentAngle.setAngle(currentAngle.getAngle() + angleChange);
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
  double xTranslationR = cos(currentAngle.getAngle()) * traveledDistanceR;
  double yTranslationR = sin(currentAngle.getAngle()) * traveledDistanceR;

  double xTranslationL = cos(currentAngle.getAngle()) * traveledDistanceL;
  double yTranslationL = sin(currentAngle.getAngle()) * traveledDistanceL;

  double finalXTranslation = (xTranslationR + xTranslationL) / 2.0;
  double finalYTranslation = (yTranslationR + yTranslationL) / 2.0;

  currentX += finalXTranslation;
  currentY += finalYTranslation;

  pros::lcd::print(0, "(%f, %f", currentX, currentY);
  pros::lcd::print(1, "Cur Angle: %f", currentAngle.getAngle());

  prevFRDrive = frDrive;
  prevBRDrive = brDrive;
  prevFLDrive = flDrive;
  prevBLDrive = blDrive;
}

bool Chassis::driveToPoint(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion)
{
  std::shared_ptr<DriveMovement> currentMovementPointer = getFirstMovement();
  DriveMovement currentMovement = *(currentMovementPointer.get());

  const double xTolerance = .2;
  const double yTolerance = .2;
  const double errorTolerance = 1.5;
  const double angleErrorTolerance = PI / 12.0;
  const double angleAdjustmentKP = 4000.0;
  const double errorInnerRange = 3.0; //Minimum distance the robot can be for anglePID to be turned on

  double xDistance = x - currentX;
  double yDistance = y - currentY;

  double error = distance(x, y, currentX, currentY);
  double speed = error * kp;

  if (fabs(xDistance) < .25)
  {
    xDistance = 0.0;
  }
  if (fabs(yDistance) < .25)
  {
    yDistance = 0.0;
  }

  Angle targetAngle(atan2(yDistance, xDistance));

  if (currentMovement.turnTargetAngleIsSet == false)
  {
    currentMovementPointer.get()->setTargetAngle(targetAngle.getAngle());
    currentMovementPointer.get()->turnTargetAngleIsSet = true;
  }

  if (fabs(targetAngle.getAngle()) < .09)
  {
    targetAngle.setAngle(0.0);
  }

  double angleDifference = calculateShortestAngleDiff(currentAngle.getAngle(), currentMovementPointer.get()->getTargetAngle());

  pros::lcd::print(2, "%f, %f", xDistance, yDistance);
  pros::lcd::print(3, "%f, %f, %f", targetAngle.getAngle(), currentMovementPointer.get()->getTargetAngle(), angleDifference);

  if (fabs(speed) < speedDeadband)
  {
    speed = speedDeadband * sign(speed);
  }

  if (fabs(error) > errorInnerRange)
  {
    if (fabs(angleDifference) > angleErrorTolerance)
    {
      turnToTarget(currentMovementPointer.get()->getTargetAngle(), DriveMovement::TURN_DEFAULT_SPEED_DEADBAND,
                   DriveMovement::TURN_DEFAULT_KP - 2000.0, false);
      return false;
    }
    else
    {
      currentMovementPointer.get()->turnTargetAngleIsSet = false;
      moveRightDriveVoltage(0);
      moveLeftDriveVoltage(0);
      return true;
    }
  }
  else if (error > errorTolerance)
  {
    if (angleDifference > degreeToRadian(85) && angleDifference < degreeToRadian(95))
    {
      moveRightDriveVoltage(0);
      moveLeftDriveVoltage(0);
      return true;
    }
    else if (targetAngle.getAngle() > 0 && targetAngle.getAngle() < PI)
    {
      moveRightDriveVoltage(abs(speed));
      moveLeftDriveVoltage(abs(speed));
      return false;
    }
    else
    {
      moveRightDriveVoltage(abs(speed) * -1);
      moveLeftDriveVoltage(abs(speed) * -1);
      return false;
    }
  }
  else
  {
    moveRightDriveVoltage(0);
    moveLeftDriveVoltage(0);
    return true;
  }
}

void Chassis::driveToPointSync(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion)
{
  const double xTolerance = .2;
  const double yTolerance = .2;
  const double errorTolerance = .75;
  const double angleErrorTolerance = degreeToRadian(7);
  const double angleAdjustmentKP = 4000.0;
  const double errorInnerRange = 3.0; //Minimum distance the robot can be for anglePID to be turned on

  double xDistance = x - currentX;
  double yDistance = y - currentY;

  double error = distance(x, y, currentX, currentY);
  double speed = error * kp;

  Angle targetAngle(atan2(yDistance, xDistance));
  double angleDifference = calculateShortestAngleDiff(targetAngle.getAngle(), currentAngle.getAngle());

  while (fabs(error) > errorTolerance)
  {
    xDistance = x - currentX;
    yDistance = y - currentY;

    error = distance(x, y, currentX, currentY);
    speed = error * kp;

    targetAngle.setAngle(atan2(yDistance, xDistance));
    angleDifference = calculateShortestAngleDiff(targetAngle.getAngle(), currentAngle.getAngle());

    if (fabs(speed) < speedDeadband)
    {
      speed = speedDeadband * sign(speed);
    }

    pros::lcd::print(2, "%f, %f, %f", xDistance, yDistance, error);
    pros::lcd::print(3, "%f, %f, %f", speed, targetAngle.getAngle(), angleDifference);

    if (fabs(error) > errorInnerRange)
    {

      if (fabs(angleDifference) > angleErrorTolerance)
      {
        turnToTargetSync(targetAngle.getAngle(), DriveMovement::TURN_DEFAULT_SPEED_DEADBAND,
                         DriveMovement::TURN_DEFAULT_KP - 2000.0, false);
      }
      else
      {
        pros::lcd::print(4, "Outer range");
        moveRightDriveVoltage(speed);
        moveLeftDriveVoltage(speed);
      }
    }
    else
    {
      if (angleDifference > degreeToRadian(85) && angleDifference < degreeToRadian(95))
      {
        pros::lcd::print(4, "Inner range 1");
        moveRightDriveVoltage(0);
        moveLeftDriveVoltage(0);
        break;
      }
      else if (calculateShortestAngleDiff(currentAngle, targetAngle) < (PI / 2.0))
      {
        //If the robot is facing an angle where forwards will get closer to the target
        pros::lcd::print(4, "Inner range 2");
        moveRightDriveVoltage(abs(speed));
        moveLeftDriveVoltage(abs(speed));
      }
      else
      {
        //If the robot is facing an angle where backwards will get closer to the target
        pros::lcd::print(4, "Inner range 3");
        moveRightDriveVoltage(abs(speed) * -1);
        moveLeftDriveVoltage(abs(speed) * -1);
      }
    }
    pros::delay(30);
  }
  moveRightDriveVoltage(0);
  moveLeftDriveVoltage(0);
}

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, double kp, bool stopOnCompletion)
{

  //This function is still missing shortest path addition to choose which direction
  //is the quickest to reach desired angle

  const double tolerance = .1;
  const double speedTolerance = 5;
  /*if (abs(targetAngle - currentAngle) > abs((targetAngle + ((targetAngle > 0) ? (-2 * PI) : (2 * PI)) - currentAngle)))
  {
    targetAngle = ((targetAngle > 0) ? (-2 * PI) : (2 * PI));
  } //find shortest direction to target angle*/
  double error = targetAngle - currentAngle.getAngle();
  double driveSpeed = error * kp;
  // pros::lcd::print(3, "%f", driveSpeed);
  // pros::lcd::print(4, "%f", currentAngle);
  // pros::lcd::print(5, "%f", fabs(error));

  if (fabs(error) > tolerance || frontRightDrive.get_actual_velocity() > speedTolerance)
  {
    error = targetAngle - currentAngle.getAngle();
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

void Chassis::turnToTargetSync(Angle targetAngle, int speedDeadband, double kp, bool stopOnCompletion)
{

  const double tolerance = .1;
  const double speedTolerance = 5;

  double angleDifference = calculateShortestAngleDiff(targetAngle.getAngle(), currentAngle.getAngle());
  double error = targetAngle.getAngle() - currentAngle.getAngle();
  double speed = error * kp;

  while (fabs(error) > tolerance)
  {
    angleDifference = calculateShortestAngleDiff(targetAngle.getAngle(), currentAngle.getAngle());
    error = targetAngle.getAngle() - currentAngle.getAngle();
    if (fabs(error) != angleDifference)
    {
      error = angleDifference * sign(error) * -1.0;
    }
    pros::lcd::print(4, "%f, %f", angleDifference, error);
    speed = error * kp;

    if (fabs(speed) < speedDeadband)
    {
      speed = speedDeadband * sign(speed);
    }

    moveRightDriveVoltage(speed * -1.0);
    moveLeftDriveVoltage(speed);

    pros::delay(30);
  }
  moveRightDriveVoltage(0);
  moveLeftDriveVoltage(0);
}

/*
This function invokes all actions that belong to the chassis subsytem that need to be iterated over.  
 */
// void chassisTaskActions(void *param)
// {
//   int i = 0;
//   pros::delay(10000);
//   chassis.sensorInit();
//   while (true)
//   {
//     // if (i < 3)
//     // {
//     //   chassis.sensorInit();
//     //   i++;
//     // } //This worked, but it's a terrible way of doing it.
//     //pros::lcd::print(7, "%d", pros::Task::get_count());
//     chassis.trackPosition();
//     //chassis.printCoords();
//     //chassis.completeMovements();
//     i++;
//     pros::lcd::print(6, "Task %d", i);
//     pros::lcd::print(7, "%f", chassis.currentAngle);
//     pros::delay(10);
//   }
// }

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

//pros::Task chassisControl(chassisTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Chassis Subsystem Task");

void chassisTaskActions(void *param)
{
  while (true)
  {
    chassis.completeMovements();
    pros::delay(30);
  }
}

void chassisOdometry(void *param)
{
  while (true)
  {
    chassis.trackPosition();
    pros::delay(30);
  }
} //run odometry code seperately from complete movements to allow complete Movements to sometimes be blocking and not prevent position tracking from running

pros::Task chassisOdometryTask(chassisOdometry, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "ChassisOdom");
pros::Task chassisControl(chassisTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "ChassisTask");