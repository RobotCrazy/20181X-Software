#include "main.h"

TrayTilter::TrayTilter(int tilterPort) : tilter(tilterPort)
{
  tilter.tare_position();
}

void TrayTilter::init()
{
  tilter.tare_position();
}

void TrayTilter::driverControl()
{
  /* if (moveTilterRequested == true)
  {
    moveToTargetPos();
  }
  else
  {*/
  tilter.move((master.get_digital(DIGITAL_A) * -70) - (master.get_digital(DIGITAL_B) * -100));
  /*}*/
}

int TrayTilter::getPosition()
{
  return tilter.get_position();
}

void TrayTilter::move(int speed)
{
  tilter.move(speed);
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

void TrayTilter::setTargetPos(int target)
{
  moveTilterRequested = true;
  targetPos = target;
}

void TrayTilter::moveToTargetPos()
{
  int error = targetPos - tilter.get_position();
  if (error > 10)
  {
    tilter.move(-80);
  }
  else if (error < 10)
  {
    tilter.move(80);
  }
  else
  {
    tilter.move(0);
  }
}