#include "main.h"
#include "utility/prereq.hpp"

bool forwardToCubePFunc()
{
  return (1 == 1);
}
bool drivingToPointPFunc()
{
  return (1 == 1);
}
void auto1()
{
  Prereq forwardToCubePrereq(forwardToCubePFunc);

  DriveMovement forwardToCube2(0, 10);
  forwardToCube2.setDrivePrereq(forwardToCubePrereq);
  forwardToCube2.setStopOnCompletion(true);
  chassis.addMovement(forwardToCube2);

  // DriveMovement drivingToPoint(10, 10);
  // Prereq drivingToPointPrereq(drivingToPointPFunc);
  // drivingToPoint.setDrivePrereq(drivingToPointPrereq);
  // drivingToPoint.setStopOnCompletion(true);
  // chassis.addMovement(drivingToPoint);
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
