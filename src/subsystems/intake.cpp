#include "main.h"

Intake::Intake(int intakePort)
    : intake(intakePort)
{
}

void Intake::driverControl()
{
  intake.move(master.get_digital(DIGITAL_R1) * 127);
}