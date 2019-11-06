#include "main.h"

pros::Motor intake2(16);
Intake::Intake(int intakePortLeft, int intakePortRight)
    : intakeLeft(intakePortLeft), intakeRight(intakePortRight)
{
}

void Intake::driverControl()
{
  intakeLeft.move(master.get_digital(DIGITAL_R1) * 127 - (master.get_digital(DIGITAL_R2) * 127));
  intakeRight.move(master.get_digital(DIGITAL_R1) * -127 - (master.get_digital(DIGITAL_R2) * -127));
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
  if (movements.empty() == false)
  {
    //pros::lcd::print(6, "Inside if statement");
    IntakeMovement im = getFirstMovement();
    if (im.readyToOperate() == true)
    {
      runIntake(5000);
    }
  }
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