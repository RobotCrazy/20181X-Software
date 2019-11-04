#include "main.h"

Lift::Lift(int liftPort) : liftMotor(liftPort)
{
}

void Lift::driverControl()
{
  if (master.get_digital(DIGITAL_L1))
  {
    liftMotor.move_voltage(10000);
  }
  else if (master.get_digital(DIGITAL_L2))
  {
    liftMotor.move_voltage(-10000);
  }
  else
  {
    liftMotor.move_voltage(0);
    liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
  }
}