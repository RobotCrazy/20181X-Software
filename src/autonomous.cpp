#include "main.h"
#include "utility/prereq.hpp"
#include <functional>
#include <memory>

int autoMode = 1;

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

void auto1() //Small Blue Auton
{

  intake.startIntake();

  chassis.driveRampUp('f', 26.25, 12, 7000);

  chassis.turnToTarget(45, 12000);

  chassis.driveRampUp('b', 28.75, 18, 12000);

  chassis.turnToTarget(0, 10000);

  chassis.driveRampUp('f', 38, 12, 7000);

  chassis.turnToTarget(-149, 6000);

  intake.stopIntake();

  intake.reverseIntakeForDeploy(0);

  chassis.driveRampUp('f', 39, 12, 8000);

  intake.reverseIntakeForDeploy(550);

  trayTilter.deployCubes();

  chassis.driveRampUp('b', 4, 15, 9000);


 // chassis.turnToTarget(40, 8000);

  //chassis.driveRampUp('f', 8, 12, 8000);
  // intake.startIntake();

  // chassis.driveRampUp('f', 42, 12, 8000);

  // chassis.turnToTarget(26, 12000);

  // chassis.driveRampUp('b', 43);

  // chassis.turnToTarget(-2.5, 12000);

  // chassis.driveRampUp('f', 45, 12, 7000);

  // chassis.turnToTarget(-150, 6000);

  // intake.stopIntake();

  // intake.reverseIntakeForDeploy(0);

  // chassis.driveRampUp('f', 40, 10, 7000);

  // intake.reverseIntakeForDeploy();

  // trayTilter.deployCubes();

  // chassis.driveRampUp('b', 4);
}

void auto2() //Big Blue Auton
{
  intake.startIntake();

  chassis.driveRampUp('f', 18);

  pros::delay(200);

  chassis.turnToTarget(-97.5);

  chassis.driveRampUp('f', 23, 18, 9000);

  chassis.driveRampUp('b', 8);

  chassis.driveRampUp('f', 28, 14, 8000);

  chassis.driveRampUp('b', 6);

  chassis.turnToTarget(-247, 5000);

  pros::delay(400);

  intake.stopIntake();

  intake.reverseIntakeForDeploy(0);

  // chassis.turnToTarget(-213, 8000);

  // chassis.driveRampUp('f', 45, 7, 6000);

  // intake.stopIntake();

  // intake.reverseIntakeForDeploy();







  // trayTilter.deployCubes();

  // chassis.driveRampUp('b', 10);
}

void auto3() //Small Red Auton
{

  intake.startIntake();

  chassis.driveRampUp('f', 26.25, 12, 8500);

  chassis.turnToTarget(-45, 12000);

  chassis.driveRampUp('b', 28.75, 18, 12000);

  chassis.turnToTarget(0, 10000);

  chassis.driveRampUp('f', 38, 12, 7000);

  chassis.turnToTarget(149, 6000);

  intake.stopIntake();

  intake.reverseIntakeForDeploy(0);

  chassis.driveRampUp('f', 38.25, 12, 8000);

  intake.reverseIntakeForDeploy(550);

  trayTilter.deployCubes();

  chassis.driveRampUp('b', 4, 15, 9000);

  // intake.startIntake();

  // chassis.driveRampUp('f', 42);

  // chassis.turnToTarget(-27.5);

  // chassis.driveRampUp('b', 43);

  // chassis.turnToTarget(5, 12000);

  // chassis.driveRampUp('f', 45, 12, 7000);

  // chassis.turnToTarget(154, 6000);

  // intake.stopIntake();

  // intake.reverseIntakeForDeploy(0);

  // chassis.driveRampUp('f', 43, 10, 7000);

  // intake.reverseIntakeForDeploy(350);

  // trayTilter.deployCubes();

  // chassis.driveRampUp('b', 4);
}

void auto4() //Big Red Auton
{
  intake.startIntake();

  chassis.driveRampUp('f', 18);

  pros::delay(200);

  chassis.turnToTarget(92.5);

  pros::delay(200);

  chassis.driveRampUp('f', 23, 18, 9000);

  chassis.driveRampUp('b', 8);

  chassis.driveRampUp('f', 28, 14, 8000);

  chassis.driveRampUp('b', 6);

  chassis.turnToTarget(247, 5000);

  pros::delay(400);

  intake.stopIntake();

  intake.reverseIntakeForDeploy(0);

  chassis.driveRampUp('f', 35.1, 11, 8000);

  intake.reverseIntakeForDeploy(850);

  trayTilter.deployCubes();

  pros::delay(500);

  chassis.driveRampUp('b', 9);
}

void autonSkills()
{
  intake.startIntake();

  chassis.driveRampUp('f', 42, 16, 10000);

  chassis.turnToTarget(28, 12000);

  chassis.driveRampUp('b', 45);

  chassis.turnToTarget(0, 12000);

  chassis.driveRampUp('f', 45, 12, 5000);

  chassis.turnToTarget(-152, 6000);

  intake.reverseIntakeForDeploy(0);

  intake.stopIntake();

  chassis.driveRampUp('f', 39.6, 10, 7000);

  intake.reverseIntakeForDeploy();

  trayTilter.deployCubes();

  pros::delay(500);

  chassis.driveRampUp('b', 12.5, 12, 6500);

  chassis.turnToTarget(-260, 8000);

  trayTilter.move(100);

  pros::delay(500);

  intake.startIntake();

  chassis.driveRampUp('f', 45);

  pros::delay(500);

  chassis.turnToTarget(-71, 7000);

  intake.stopIntake();

  chassis.driveRampUp('f', 27, 18, 8000);

  intake.reverseIntakeForDeploy(800);

  lift.raiseArm(2100);

  pros::delay(300);

  chassis.driveRampUp('f', 6.5);

  intake.reverseIntake(1000, 80); //Deposit cubes into blue alliance tower

  chassis.driveRampUp('b', 18.5);

  lift.lowerArm(100);

  chassis.turnToTarget(0);

  intake.startIntake();

  chassis.driveRampUp('f', 31);

  pros::delay(400);

  chassis.driveRampUp('b', 8);

  intake.reverseIntakeForDeploy(800);

  lift.raiseArm(2200);

  chassis.driveRampUp('f', 6.8);

  intake.reverseIntake(1000, 90);

  chassis.driveRampUp('b', 10);

  chassis.turnToTarget(-260);

  lift.lowerArm(0);

  intake.startIntake();

  chassis.driveRampUp('f', 25);
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
  autoMode = 3;
  if (autoMode == 1)
  {
    auto1();
  }
  else if (autoMode == 2)
  {
    auto2();
  }
  else if (autoMode == 3)
  {
    auto3();
  }
  else if (autoMode == 4)
  {
    auto4();
  }
  else
  {
    autonSkills();
  }
}
