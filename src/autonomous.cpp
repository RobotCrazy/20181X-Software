#include "main.h"
#include "utility/prereq.hpp"
#include <functional>
#include <memory>

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

void autoTest()
{
  // std::shared_ptr<DriveMovement> drivingToPoint2 = std::make_shared<DriveMovement>(20, 10);
  // std::shared_ptr<Prereq> drivingToPoint2Prereq = std::make_shared<Prereq>([&]() {
  //   return (1 == 1);
  // });
  // drivingToPoint2.get()->setDrivePrereq(drivingToPoint2Prereq);

  // chassis.addMovement(drivingToPoint2);

  // std::shared_ptr<DriveMovement> turnMovement = std::make_shared<DriveMovement>(10);
  // std::shared_ptr<Prereq> turnMovementPrereq = std::make_shared<Prereq>(std::list<std::shared_ptr<DriveMovement>>({drivingToPoint2}));

  // turnMovement.get()->setDrivePrereq(turnMovementPrereq);
  // chassis.addMovement(turnMovement);

  // Prereq p([&]() {
  //   return drivingToPoint2.isComplete();
  // }, drivingToPoint2)

  /*std::shared_ptr<DriveMovement> drivingToPoint2 = std::make_shared<DriveMovement>(degreeToRadian(180));
  chassis.addMovement(drivingToPoint2);

  std::shared_ptr<DriveMovement> drivingToPoint3 = std::make_shared<DriveMovement>(degreeToRadian(-720));
  chassis.addMovement(drivingToPoint3);*/

  std::shared_ptr<DriveMovement> driveToPoint = std::make_shared<DriveMovement>(0, 20);
  chassis.addMovement(driveToPoint);

  std::shared_ptr<DriveMovement> turn1 = std::make_shared<DriveMovement>(PI / 4.0);
  chassis.addMovement(turn1);

  std::shared_ptr<DriveMovement> driveToPoint2 = std::make_shared<DriveMovement>(10, 15);
  chassis.addMovement(driveToPoint2);

  std::shared_ptr<DriveMovement> driveToPoint3 = std::make_shared<DriveMovement>(22, 40);
  chassis.addMovement(driveToPoint3);

  std::shared_ptr<DriveMovement> turn2 = std::make_shared<DriveMovement>(degreeToRadian(330));
  chassis.addMovement(turn2);

  std::shared_ptr<DriveMovement> driveToPoint4 = std::make_shared<DriveMovement>(0, 0);
  chassis.addMovement(driveToPoint4);

  // std::shared_ptr<DriveMovement> turn1 = std::make_shared<DriveMovement>(degreeToRadian(330));
  // chassis.addMovement(turn1);
}

void auto1()
{
  std::shared_ptr<DriveMovement> deployMovement = std::make_shared<DriveMovement>(0, 12);
  deployMovement->setStopOnCompletion(false);
  chassis.addMovement(deployMovement);

  chassis.waitUntilSettled();

  lift.deploy();

  intake.startIntake();

  std::shared_ptr<DriveMovement> pickUpCubes = std::make_shared<DriveMovement>(0, 55);
  pickUpCubes->setMaxSpeed(5000);
  chassis.addMovement(pickUpCubes);

  std::shared_ptr<DriveMovement> pickUpCubes2 = std::make_shared<DriveMovement>(0, 65);
  pickUpCubes->setMaxSpeed(6000);
  chassis.addMovement(pickUpCubes2);

  chassis.waitUntilSettled();

  intake.stopIntake();

  std::shared_ptr<DriveMovement> deployCubesDrive = std::make_shared<DriveMovement>(-13.25, 5);
  pickUpCubes->setMaxSpeed(6000);
  pickUpCubes->setStopOnCompletion(true);
  chassis.addMovement(deployCubesDrive);

  chassis.waitUntilSettled();
  pros::lcd::print(6, "About to deploy cubes");

  trayTilter.deployCubes();

  pros::lcd::print(6, "Done deploying");
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
