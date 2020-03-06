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

void displayGyroValues() {
  chassis.gyro.reset();
  
  pros::delay(1000);
  while(true) {
    char buf[32];
    snprintf(buf, 32, "%f", chassis.gyro.get_value() / GYRO_SCALE / 10.0);
    lv_label_set_text(feedbackLabel, buf);
    pros::delay(20);
  }
}


void auto1() //Small Blue Auton
{
  intake.startIntake();
  intake.startIntake();
  intake.startIntake();
  pros::delay(20);
  intake.startIntake();
  pros::delay(20);
  intake.startIntake();

  chassis.driveRampUp('f', 26.75, 10, 5000);

  chassis.turnToTarget(47, 10500);

  chassis.driveRampUp('b', 29, 18);

  chassis.turnToTarget(-2.25, 9000);

  chassis.driveRampUp('f', 34, 12, 5000);

  chassis.turnToTarget(-163, 6500);

  chassis.setGlobalTargetAngle(chassis.gyro.get_value());

  chassis.driveRampUp('f', 34.2, 15, 10000);

  intake.stopIntake();

  trayTilter.deployCubes();

  //Deploy cubes 

  intake.runIntakeAt(-90);

  chassis.driveRampUp('b', 6, 30);

  intake.runIntakeAt(0);

} 

void auto2() //Big Blue Auton
{
  intake.startIntake();

  chassis.driveRampUp('f', 29, 12, 7000);

  pros::delay(250);

  chassis.turnToTarget(-47, 12000);

  chassis.driveRampUp('b', 32, 22, 12000);

  chassis.turnToTarget(0, 8000);

  chassis.driveRampUp('f', 40, 12, 7000);

  chassis.turnToTarget(153, 7000);

  intake.stopIntake();

  intake.reverseIntakeForDeploy(0);

  chassis.driveRampUp('f', 36, 13, 8000);

  intake.reverseIntakeForDeploy(250);

  trayTilter.deployCubes();

  chassis.driveRampUp('b', 6, 15, 9000);
}

void auto3() //Small Red Auton
{

  intake.startIntake();

  chassis.driveRampUp('f', 26.75, 10, 5000);

  chassis.turnToTarget(-47, 10500);

  chassis.driveRampUp('b', 30.5, 18);

  chassis.turnToTarget(-2.5, 9000);

  chassis.driveRampUp('f', 38, 12, 6500);

  chassis.turnToTarget(155, 6500);

  chassis.setGlobalTargetAngle(chassis.gyro.get_value());

  chassis.driveRampUp('f', 34.75, 15, 10000);

  intake.stopIntake();

  trayTilter.deployCubes();

  intake.runIntakeAt(-90);

  chassis.driveRampUp('b', 6, 30);

  intake.runIntakeAt(0);
}

void auto4() //Big Red Auton
{
  intake.startIntake();

  chassis.driveRampUp('f', 18);

  pros::delay(200);

  chassis.turnToTarget(100);

  pros::delay(200);

  chassis.driveRampUp('f', 40, 18, 5000);

  chassis.driveRampUp('b', 28);

  chassis.turnToTarget(235);

  chassis.driveRampUp('f', 13);

  trayTilter.deployCubes();

  intake.runIntakeAt(-90);

  trayTilter.setTargetPos(2540);

  chassis.driveRampUp('b', 6, 30);

  intake.runIntakeAt(0);
}

void auto5() {
  intake.startIntake();

  chassis.driveRampUp('f', 14.25);

  pros::delay(200);

  chassis.turnToTarget(90);

  pros::delay(200);

  chassis.driveRampUp('f', 23, 18, 9000);

  chassis.driveRampUp('b', 8);

  chassis.driveRampUp('f', 25.5, 14, 8000);

  pros::delay(400);

  chassis.driveRampUp('b', 32);

  intake.stopIntake();

  chassis.turnToTarget(202.75);

  chassis.driveRampUp('f', 12.5, 8, 6000);

  intake.reverseIntakeForDeploy(550);

  trayTilter.deployCubes();

  chassis.driveRampUp('b', 5, 12, 5000);
}

void autonSkills()
{

/*  intake.startIntake();

  pros::delay(2500);

  intake.stopIntake();

  trayTilter.deployCubes();

  intake.runIntakeAt(-90);

  chassis.driveRampUp('b', 6, 30);*/

/*  trayTilter.deployCubes();

  trayTilter.setTargetPos(90);*/


  intake.startIntake();
  intake.startIntake();
  intake.startIntake();
  pros::delay(20);
  intake.startIntake();
  pros::delay(20);
  intake.startIntake();

  chassis.driveRampUp('f', 26.75, 10, 5000);

  chassis.turnToTarget(47, 10500);

  chassis.driveRampUp('b', 29, 18);

  chassis.turnToTarget(-2.25, 9000);

  chassis.driveRampUp('f', 34, 12, 5000);

  chassis.turnToTarget(-163, 6500);

  chassis.setGlobalTargetAngle(chassis.gyro.get_value());

  chassis.driveRampUp('f', 34.3, 15, 10000);

  intake.stopIntake();

  trayTilter.deployCubes();

  //Deploy cubes 

  intake.runIntakeAt(-90);

  chassis.driveRampUp('b', 6, 30);

  intake.runIntakeAt(0);

  chassis.driveRampUp('b', 37);

  trayTilter.setTargetPos(2540);

  chassis.turnToTarget(-7.5, 8000);

  intake.startIntake();

  chassis.driveRampUp('f', 16, 15, 5000);

  chassis.driveRampUp('b', 5);

  intake.stopIntake();

  intake.reverseIntakeForDeployAsync();

  pros::delay(250);

  //Raise arm for first tower

  lift.raiseArm(LIFT_MIDDLE_TOWER_POS);

  intake.setDeploySetUpRequestedFalse();

  intake.reverseIntake(700, 85);

  chassis.setGlobalTargetAngle(chassis.gyro.get_value());

  chassis.driveRampUp('b', 3.25);

  lift.lowerArm(100);

  chassis.turnToTarget(61.25);

  intake.startIntake();

  chassis.driveRampUp('f', 13, 14, 8000);

  chassis.turnToTarget(237, 7000);

  intake.reverseIntakeForDeployAsync();

  pros::delay(200);

  lift.raiseArm(LIFT_MIDDLE_TOWER_POS); //Raise arm for second tower

  chassis.driveRampUp('f', 25.5);

  intake.setDeploySetUpRequestedFalse();

  intake.reverseIntake(700, 85); //Spit into second tower

  chassis.driveRampUp('b', 6);

  lift.lowerArm(100);

  chassis.turnToTarget(70, 7000);

  intake.startIntake();

  chassis.driveRampUp('f', 32, 14, 4500);
  
  pros::delay(250);

  intake.reverseIntakeForDeployAsync();

  chassis.driveRampUp('b', 5.25);

  chassis.turnToTarget(50, 7000);

  lift.raiseArm(LIFT_HIGH_TOWER_POS);

  intake.setDeploySetUpRequestedFalse();

  chassis.driveRampUp('f', 3);

  intake.reverseIntake(700, 105); //Put cube into third tower

  chassis.driveRampUp('b', 3);

  chassis.turnToTarget(-40, 7000);

  lift.lowerArm(100);

  intake.startIntake();

  chassis.driveRampUp('f', 39, 15, 7000);

  chassis.turnToTarget(14, 8000);

  chassis.driveRampUp('f', 38, 14, 6500);

  chassis.driveRampUp('b', 15);

  chassis.turnToTarget(61, 8000);

  chassis.driveRampUp('f', 43.25);

  intake.stopIntake();

  trayTilter.deployCubes();

  intake.runIntakeAt(-90);

  chassis.driveRampUp('b', 10, 30);

  intake.runIntakeAt(0);
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

  if(autonSelection == -1) {
    
  }
  else if (autonSelection == 1)
  {
    auto1();
  }
  else if (autonSelection == 2)
  {
    auto2();
  }
  else if (autonSelection == 3)
  {
    auto3();
  }
  else if (autonSelection == 4)
  {
    auto4();
  }
  else if(autonSelection == 5) {
    auto5();
  }
  else if(autonSelection == 6) {

  }
  else
  {
    autonSkills();
  }
}
