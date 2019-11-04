#include "main.h"

TrayTilter::TrayTilter(int tilterPort) : tilter(tilterPort)
{
}

void TrayTilter::driverControl()
{
  tilter.tare_position();
}

int TrayTilter::getPosition()
{
  return tilter.get_position();
}

void TrayTilter::deployCubesOP(pros::controller_digital_e_t button)
{
  int error = DEPLOYED_POSITION - tilter.get_position();
  int kp = 100;
  int speed = error * kp;
  int prevSpeed = speed;
  while (master.get_digital(button) && tilter.get_position() < DEPLOYED_POSITION)
  {
    error = DEPLOYED_POSITION - tilter.get_position();
    kp = 100;
    speed = error * kp;
    if (speed - prevSpeed > 50)
    {
      speed = prevSpeed + 50;
    }

    tilter.move_voltage(speed);

    prevSpeed = speed;

    pros::delay(30);
  }
  tilter.move_voltage(0);
}