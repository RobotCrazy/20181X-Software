#include "main.h"

Lift::Lift(int liftPort) : liftMotor(liftPort)
{
}

void Lift::init()
{
  liftMotor.tare_position();
}

void Lift::driverControl()
{
  if (master.get_digital(DIGITAL_L1) && trayTilter.getPosition() < 720)
  {
    trayTilter.setTargetPos(720);
    liftMotor.move(100);
  }
  else if (master.get_digital(DIGITAL_L2))
  {
    trayTilter.moveTilterRequested = false;
    liftMotor.move(-100);
  }
  else
  {
    trayTilter.moveTilterRequested = false;
    liftMotor.move(0);
    liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
  }
}