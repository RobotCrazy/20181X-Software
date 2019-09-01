#include "main.h"
#include "utility/prereq.hpp"
#include <functional>

bool forwardToCubePFunc()
{
  return (1 == 1);
}
bool drivingToPointPFunc()
{
  return (1 == 1);
}
// bool runningIntakePFunc()
// {
//   return forwardToCube2.isComplete();
// }

void auto1()
{

  //chassis.addMovement(forwardToCube2);

  Prereq turnTo180Prereq([&]() {
    return (1 == 1);
  });

  // DriveMovement turnTo180(degreeToRadian(180));
  // turnTo180.setDrivePrereq(turnTo180Prereq);
  // turnTo180.setStopOnCompletion(true);
  // DriveMovement *action = &turnTo180;
  // chassis.addMovement(&turnTo180);
  // pros::lcd::print(5, "Adding movements %d %f", (&turnTo180), (*(&turnTo180)).getKP());

  // Prereq turnTo0Prereq([&]() {
  //   pros::lcd::print(7, "%d", turnTo180.isComplete());
  //   return turnTo180.isComplete();
  // });
  // DriveMovement turnTo0(0);
  // turnTo0.setDrivePrereq(turnTo0Prereq);
  // turnTo0.setStopOnCompletion(true);
  // chassis.addMovement(&turnTo0);

  /*IntakeMovement runIntakeMovement(1000);
  Prereq runIntakeMovementPrereq(forwardToCubePFunc);
  runIntakeMovement.setIntakePrereq(runIntakeMovementPrereq);
  intake.addMovement(runIntakeMovement);*/

  DriveMovement drivingToPoint(10, 10);
  Prereq drivingToPointPrereq(drivingToPointPFunc);
  drivingToPoint.setDrivePrereq(drivingToPointPrereq);
  drivingToPoint.setStopOnCompletion(true);
  chassis.addMovement(drivingToPoint);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
  auto1();
}
