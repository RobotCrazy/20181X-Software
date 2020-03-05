#include "main.h"
#include "utility/mathUtil.h"

pros::Motor intake2(16);
Intake::Intake(int intakePortLeft, int intakePortRight, char intakeLineSensorPort)
    : intakeLeft(intakePortLeft), intakeRight(intakePortRight), intakeLineSensor(intakeLineSensorPort)
{
  deploySetUpRequested = false;
}

void Intake::driverControl()
{
  setDeploySetUpRequestedFalse();
  if(master.get_digital(DIGITAL_RIGHT)) {
    intakeLeft.move(20);
    intakeRight.move(20);
  }

  else {
    intakeLeft.move(master.get_digital(DIGITAL_R1) * 127 - (master.get_digital(DIGITAL_R2) * 70));
    intakeRight.move(master.get_digital(DIGITAL_R1) * -127 - (master.get_digital(DIGITAL_R2) * -70));
    intakeLeft.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
    intakeRight.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
  }
}

void Intake::runIntake(int ticks)
{
  intakeLeft.move_relative(ticks, 80);
  intakeRight.move_relative(ticks, 80);
  while (!(intakeLeft.is_stopped()) || !(intakeRight.is_stopped()))
  {
    pros::delay(40);
  }
}

void Intake::addMovement(IntakeMovement im)
{
  movements.push(im);
}

IntakeMovement Intake::getFirstMovement()
{
  return movements.front();
}

void Intake::deleteFirstMovement()
{
  movements.pop();
}

void Intake::completeMovements()
{
  if(deploySetUpRequested == true) {
    if(intakeLineSensor.get_value() > 2550) {
      intakeLeft.move_velocity(-80);
      intakeRight.move_velocity(80);
    }
    else {
      intakeLeft.move_velocity(0);
      intakeRight.move_velocity(0);
    }
  }
}

void Intake::startIntake()
{
  intakeLeft.move_velocity(180);
  intakeRight.move_velocity(-180);
}

void Intake::stopIntake()
{
  intakeLeft.move_velocity(0);
  intakeRight.move_velocity(0);
}

void Intake::reverseIntakeForDeploy(int ms)
{
  intakeLeft.move(-40);
  intakeRight.move(40);
  pros::delay(ms);
  intakeLeft.move(10);
  intakeRight.move(-10);
}

void Intake::reverseIntakeForDeployAsync() {
   deploySetUpRequested = true;
  // while(intakeLineSensor.get_value() > 2550) {
  //     intakeLeft.move_velocity(-65);
  //     intakeRight.move_velocity(65);
  //   }
    
  //   intakeLeft.move_velocity(0);
  //   intakeRight.move_velocity(0);
}

void Intake::setDeploySetUpRequestedFalse() {
  deploySetUpRequested = false;
}

void Intake::reverseIntake(int ms, int speed)
{
  intakeLeft.move(-1 * speed);
  intakeRight.move(speed);
  pros::delay(ms);
  intakeLeft.move(0);
  intakeRight.move(0);
}

void Intake::runIntakeAt(int speed) {
    intakeLeft.move(speed);
    intakeRight.move(-1 * speed);
}

void Intake::runIntakeForAsync(int ticks) {
  intakeLeft.move_relative(ticks, 100);
  intakeLeft.move_relative(-ticks, 100);
}

void intakeTaskActions(void *param)
{

  while (true)
  {
    intake.completeMovements();
    pros::delay(30);
  }
}

pros::Task intakeControl(intakeTaskActions, param, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "IntakeTask");