#include "main.h"

TrayTilter::TrayTilter(int tilterPort, char tilterPotPort) : tilter(tilterPort), tilterPot(tilterPotPort)
{
  tilter.tare_position();
}

void TrayTilter::init()
{
  tilter.tare_position();
}

void TrayTilter::driverControl()
{
  //tilter.move((master.get_digital(DIGITAL_A) * -85) - (master.get_digital(DIGITAL_B) * -100));

  if(master.get_digital(DIGITAL_A)) {
    deployCubesOP();
  }
  else if(master.get_digital(DIGITAL_B)) {
    tilter.move(100);
  }
  else {
    tilter.move(0);
  }
}

int TrayTilter::getPosition()
{
  return tilter.get_position();
}

void TrayTilter::move(int speed)
{
  tilter.move_absolute(50, speed);
}

void TrayTilter::deployCubes()
{
  tilter.tare_position();
  // pros::lcd::print(7, "Deploying cubes");
  while (abs(tilterPot.get_value()) < DEPLOYED_POSITION)
  {
    double error = (double)(DEPLOYED_POSITION) - (double)(tilterPot.get_value());
    double kp = .11;
    if(error < 400) {
      kp = 0.1;
    }
    double speed = error * kp;
    tilter.move_velocity(-(speed + 18));
    intake.runIntakeAt(-15);
      pros::delay(30);
    }
    tilter.move(0);
    tilter.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
}

void TrayTilter::deployCubesOP()
{
  double error = (double)(DEPLOYED_POSITION) - (double)(tilterPot.get_value());
  double kp = .1;
  if(error < 400) {
    kp = 0.05;
  }
  double speed = error * kp;
  tilter.move_velocity(-(speed + 10));
  intake.runIntakeAt(-15);
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