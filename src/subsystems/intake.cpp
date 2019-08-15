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
    }
  }
}