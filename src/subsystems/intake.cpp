#include "main.h"

pros::Motor intake2(16);
Intake::Intake(int intakePort)
    : intake(intakePort)
{
}

void Intake::driverControl()
{
  intake.move(master.get_digital(DIGITAL_R1) * -127);
  intake2.move(master.get_digital(DIGITAL_R1) * 127);
}

void Intake::runIntake(int ticks)
{
  intake.move_relative(ticks, 80);
  while (!(intake.is_stopped()))
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