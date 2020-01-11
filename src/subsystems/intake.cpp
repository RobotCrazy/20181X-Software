#include "main.h"

pros::Motor intake2(16);
Intake::Intake(int intakePortLeft, int intakePortRight)
    : intakeLeft(intakePortLeft), intakeRight(intakePortRight)
{
}

void Intake::driverControl()
{
  if(master.get_digital(DIGITAL_RIGHT)) {
    intakeLeft.move(20);
    intakeRight.move(20);
  }

  else {
    intakeLeft.move(master.get_digital(DIGITAL_R1) * 127 - (master.get_digital(DIGITAL_R2) * 127));
    intakeRight.move(master.get_digital(DIGITAL_R1) * -127 - (master.get_digital(DIGITAL_R2) * -127));
    //intakeLeft.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
    //intakeRight.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_COAST);
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
  if (movements.empty() == false)
  {
    //pros::lcd::print(6, "Inside if statement");
    IntakeMovement im = getFirstMovement();
    if (im.readyToOperate() == true)
    {
      runIntake(im.getDegrees());
    }
  }
}

void Intake::startIntake()
{
  intakeLeft.move(127);
  intakeRight.move(-127);
}

void Intake::stopIntake()
{
  intakeLeft.move(0);
  intakeRight.move(0);
}

void Intake::reverseIntakeForDeploy(int ms)
{
  intakeLeft.move(-40);
  intakeRight.move(40);
  pros::delay(ms);
  intakeLeft.move(10);
  intakeRight.move(-10);
}

void Intake::reverseIntake(int ms, int speed)
{
  intakeLeft.move(-1 * speed);
  intakeRight.move(speed);
  pros::delay(ms);
  intakeLeft.move(0);
  intakeRight.move(0);
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