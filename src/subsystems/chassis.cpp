#include "main.h"
#include "utility/mathUtil.h"

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

void Chassis::setCurrentAngle(double angle)
{
  currentAngle = angle;
}

void Chassis::printCoords()
{
  pros::lcd::print(3, "%f", currentX);
  pros::lcd::print(4, "%f", currentY);
  pros::lcd::print(5, "%f", currentAngle);
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
    pros::lcd::print(4, "KP: %f", dm.getKP());
    //pros::lcd::print(5, "%d", dm->getMovementType());
    if (dm.readyToOperate() == true)
    {
      if (dm.getMovementType() == DRIVE_MOVEMENT_POINT)
      {
        pros::lcd::print(5, "Type: %d", dm.getMovementType());
        if (driveToPoint(dm.getTargetX(), dm.getTargetY(), dm.getSpeedDeadband(), dm.getMaxSpeed(), dm.getKP(), dm.getStopOnCompletion()) == true)
        {
          dmPointer.get()->setComplete();
          completedMovements.push_back(dmPointer);
          deleteFirstMovement();
        }
      }

      else if (dm.getMovementType() == DRIVE_MOVEMENT_TURN)
      {
        pros::lcd::print(5, "%d", dm.getMovementType());
        if (turnToTarget(dm.getTargetAngle(), dm.getSpeedDeadband(), dm.getKP(), dm.getStopOnCompletion()) == true)
        {
          dmPointer.get()->setComplete();
          completedMovements.push_back(dmPointer);
          deleteFirstMovement();
        }
      }
    }
    // if (dm->readyToOperate() == true)
    // {
    //   if (dm->getMovementType() == DRIVE_MOVEMENT_TURN)
    //   {
    //     if (turnToTarget(dm->getTargetAngle(), dm->getSpeedDeadband(), dm->getKP(), dm->getStopOnCompletion()) == true)
    //     {
    //       //completedMovements.push_back(&dm);
    //       deleteFirstMovement();
    //     }
    //   }
    //   else if (dm->getMovementType() == DRIVE_MOVEMENT_POINT)
    //   {
    //     driveToPoint(dm->getTargetX(), dm->getTargetY(), dm->getSpeedDeadband(), dm->getMaxSpeed(), dm->getKP(), dm->getStopOnCompletion());
    //     //completedMovements.push_back(&dm);
    //     deleteFirstMovement();
    //   }
    // }
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
  currentAngle = PI / 2.0;
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

  pros::lcd::print(1, "%f", currentX);
  pros::lcd::print(2, "%f", currentY);
  pros::lcd::print(3, "%f", currentAngle);

  prevFRDrive = frDrive;
  prevBRDrive = brDrive;
  prevFLDrive = flDrive;
  prevBLDrive = blDrive;
}

bool Chassis::driveToPoint(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion)
{
  const double angleThreshold = degreeToRadian(90);
  const double defaultAngleKP = 2000.0;
  const double errorTolerance = .25;
  const double velocityTolerance = 2.5;
  double angleKP = 1000.0; //Tune these two constants as needed
  double xDistance = x - currentX;
  double yDistance = y - currentY;
  double targetAngle = atan(fabs(yDistance) / fabs(xDistance)) + angleQuadrantAdjustment(xDistance, yDistance);
  double error = distance(currentX, currentY, x, y);
  double speed = error * kp;
  double angleDifference = currentAngle - targetAngle;
  double angleErrorThreshold = 6.0;

  pros::lcd::print(4, "%f, %f, %f, %f", x, y, xDistance, yDistance);
  pros::lcd::print(5, "%f, %f, %f", targetAngle, error, speed);

  if (abs(speed) < speedDeadband)
  {
    speed = sign(speed) * speedDeadband;
  }

  if (fabs(angleDifference) > angleThreshold && fabs(error) > angleErrorThreshold)
  {
    turnToTarget(targetAngle, DriveMovement::TURN_DEFAULT_SPEED_DEADBAND,
                 DriveMovement::TURN_DEFAULT_KP - 2000.0, DriveMovement::TURN_DEFAULT_COMPLETION_STOP);
    return false;
  }
  else if (fabs(error) > errorTolerance)
  {
    moveRightDriveVoltage(speed + (angleDifference * angleKP));
    moveLeftDriveVoltage(speed - (angleDifference * angleKP)); //It might need to be
    //addition instead of subtraction or vice versa
    return false;
  }
  else
  {
    moveRightDriveVoltage(0);
    moveLeftDriveVoltage(0);
    pros::lcd::print(7, "Done driving to point");
    return true;
  }
  return false;

  //Insert code for driving to a point with odometry here
  //This code should dynamically update its path if external factors cause the robot to
  //get off course.
  // Look at motion profiling concepts for this
}

bool Chassis::driveToPointSync(double x, double y, int speedDeadband, int maxSpeed, double kp, bool stopOnCompletion)
{

  const double angleThreshold = degreeToRadian(90);
  const double defaultAngleKP = 2000.0;
  const double errorTolerance = .25;
  const double velocityTolerance = 2.5;
  const double angleKP = 1000.0; //Tune these two constants as needed
  double xDistance = x - currentX;
  double yDistance = y - currentY;
  double targetAngle = atan(fabs(yDistance) / fabs(xDistance)) + angleQuadrantAdjustment(xDistance, yDistance);
  double error = distance(currentX, currentY, x, y);
  double speed = error * kp;
  double angleDifference = currentAngle - targetAngle;
  double angleErrorThreshold = 6.0;

  while (fabs(error) > errorTolerance)
  {
    pros::lcd::print(7, "Driving to point");
    xDistance = x - currentX;
    yDistance = y - currentY;
    targetAngle = atan(fabs(yDistance) / fabs(xDistance)) + angleQuadrantAdjustment(xDistance, yDistance);
    error = distance(currentX, currentY, x, y);
    speed = error * kp;
    angleDifference = currentAngle - targetAngle;
    angleErrorThreshold = 6.0;

    pros::lcd::print(4, "%f, %f, %f, %f", x, y, xDistance, yDistance);
    pros::lcd::print(5, "%f, %f, %f", targetAngle, error, speed);

    if (abs(speed) < speedDeadband)
    {
      speed = sign(speed) * speedDeadband;
    }

    if (fabs(angleDifference) > angleThreshold && fabs(error) > angleErrorThreshold)
    {
      turnToTarget(targetAngle, DriveMovement::TURN_DEFAULT_SPEED_DEADBAND,
                   DriveMovement::TURN_DEFAULT_KP - 2000.0, DriveMovement::TURN_DEFAULT_COMPLETION_STOP);
    }
    else if (fabs(error) > errorTolerance)
    {
      moveRightDriveVoltage(speed + (angleDifference * angleKP));
      moveLeftDriveVoltage(speed - (angleDifference * angleKP)); //It might need to be
      //addition instead of subtraction or vice versa
    }
    else
    {
      moveRightDriveVoltage(0);
      moveLeftDriveVoltage(0);
      pros::lcd::print(7, "Done driving to point");
    }

    pros::delay(50);
  }

  /*if (abs(speed) < speedDeadband)
  {
    speed = sign(speed) * speedDeadband;
  }

  if (fabs(angleDifference) > angleThreshold && fabs(error) > angleErrorThreshold)
  {
    turnToTarget(targetAngle, DriveMovement::TURN_DEFAULT_SPEED_DEADBAND,
                 DriveMovement::TURN_DEFAULT_KP - 2000.0, DriveMovement::TURN_DEFAULT_COMPLETION_STOP);
    return false;
  }
  else if (fabs(error) > errorTolerance)
  {
    moveRightDriveVoltage(speed + (angleDifference * angleKP));
    moveLeftDriveVoltage(speed - (angleDifference * angleKP)); //It might need to be
    //addition instead of subtraction or vice versa
    return false;
  }
  else
  {
    moveRightDriveVoltage(0);
    moveLeftDriveVoltage(0);
    pros::lcd::print(7, "Done driving to point");
    return true;
  }*/
  return true;
}

bool Chassis::turnToTarget(double targetAngle, int speedDeadband, double kp, bool stopOnCompletion)
{

  //This function is still missing shortest path addition to choose which direction
  //is the quickest to reach desired angle

  pros::lcd::print(6, "%f   Turning to target", targetAngle);
  const double tolerance = .1;
  const double speedTolerance = 5;
  /*if (abs(targetAngle - currentAngle) > abs((targetAngle + ((targetAngle > 0) ? (-2 * PI) : (2 * PI)) - currentAngle)))
  {
    targetAngle = ((targetAngle > 0) ? (-2 * PI) : (2 * PI));
  } //find shortest direction to target angle*/
  double error = targetAngle - currentAngle;
  double driveSpeed = error * kp;
  // pros::lcd::print(3, "%f", driveSpeed);
  // pros::lcd::print(4, "%f", currentAngle);
  // pros::lcd::print(5, "%f", fabs(error));

  if (fabs(error) > tolerance || frontRightDrive.get_actual_velocity() > speedTolerance)
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
    pros::lcd::print(6, "Done turning to position");
    return true;
  }
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
    chassis.trackPosition();
    chassis.completeMovements();
    pros::delay(30);
  }
}

pros::Task chassisControl(chassisTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "ChassisTask");