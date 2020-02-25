#include "main.h"

const int LIFT_MIDDLE_TOWER_POS = 1295;
const int LIFT_HIGH_TOWER_POS = 1610;


Lift::Lift(int liftPort, char liftPotPort) : liftMotor(liftPort), liftPot(liftPotPort)
{
  liftMotor.tare_position();
  towerButtonCount = 0;
}

void Lift::raiseArm(int pos)
{
  int elapsedTime = 0;

  while (liftPot.get_value() < pos)
  {
    liftMotor.move(100);
    elapsedTime += 30;
    pros::delay(30);
    if (elapsedTime >= 3000)
    {
      break;
    }
  }
  liftMotor.move(0);
  liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
}

void Lift::lowerArm(int pos)
{
  int elapsedTime = 0;

  while (liftPot.get_value() > pos)
  {
    liftMotor.move(-100);
    elapsedTime += 30;
    pros::delay(30);
    if (elapsedTime >= 3000)
    {
      break;
    }
  }
  liftMotor.move(0);
}

void Lift::init()
{
  liftMotor.tare_position();
}

float liftTargetPos = 0;
void Lift::driverControl()
{
  if(master.get_digital_new_press(DIGITAL_L1)) {
    towerButtonCount++;
    if(towerButtonCount > 2) {
      towerButtonCount = 1;
    }
    if(towerButtonCount == 1) {
      liftTargetPos = LIFT_MIDDLE_TOWER_POS;
    }
    else if(towerButtonCount == 2) {
      liftTargetPos = LIFT_HIGH_TOWER_POS;
    }
  }
  
  else if (master.get_digital(DIGITAL_L2))
  {
    towerButtonCount = 0;
    liftTargetPos = 0;
  }
  else if(master.get_digital(DIGITAL_UP)) {
    liftTargetPos = -10;
    liftMotor.move(100);
  }
  else if(master.get_digital(DIGITAL_DOWN)) {
    liftTargetPos = -10;
    liftMotor.move(-100);
  }
  else if(master.get_digital(DIGITAL_R1)) {
    liftMotor.move(-10);
  }
  else
  {
    if(abs(liftPot.get_value() - liftTargetPos) > 50 && liftTargetPos >= 0) {
      
      double speed = 0;
      if(liftPot.get_value() < (liftTargetPos - 300)) {
        speed = 12000;
      }
      else if(liftPot.get_value() < (liftTargetPos - 50)) {
        speed = 6000;
      }
      else if(liftTargetPos < 80) {
        speed = -12000;
      }
      else if(liftPot.get_value() > (liftTargetPos + 50)) {
        speed = -4000;
      }
      else if(liftPot.get_value() > (liftTargetPos + 300)) {
        speed = -9500;
      }
      else {
        liftMotor.move(0);
        liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
      }
      liftMotor.move_voltage(speed);

      /*if(abs(liftPot.get_value() - liftTargetPos) <= 50) {
        liftMotor.move(0);
        liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
      }
      else {

        double error = liftTargetPos - liftPot.get_value();
        double kp = 25;
        double speed = error * kp;

        if(abs(speed) < 8000) {
          speed = sign(speed) * 8000;
        }
        liftMotor.move_voltage(speed);
      }
      */

      // if((liftTargetPos == LIFT_MIDDLE_TOWER_POS || liftTargetPos == LIFT_HIGH_TOWER_POS) 
      //     && liftPot.get_value() > 75 && liftPot.get_value() < 300) {
      //   intake.runIntakeAt(-110);
      // }

      // if(liftTargetPos == 0 && liftPot.get_value() > 80) {
      //   intake.runIntakeAt(90);
      // }
    }
    else {
      liftMotor.move(0);
      liftMotor.set_brake_mode(pros::motor_brake_mode_e_t::E_MOTOR_BRAKE_HOLD);
    }
  }
}

void Lift::deploy()
{
  liftMotor.tare_position();
  int target = 2000;

  int elapsedTime = 0;
  while (abs(liftMotor.get_position()) < target)
  {
    liftMotor.move(100);
    elapsedTime += 30;
    pros::delay(30);
    if (elapsedTime >= 2000)
    {
      break;
    }
  }
  elapsedTime = 0;

  pros::delay(250);

  while (liftMotor.get_position() > 20)
  {
    liftMotor.move(-100);
    pros::delay(30);
  }

  // pros::delay(250);

  // while (abs(liftMotor.get_position()) < target)
  // {
  //   liftMotor.move(100);
  //   pros::delay(30);
  // }
  // while (liftMotor.get_position() > 20)
  // {
  //   liftMotor.move(-100);
  //   pros::delay(30);
  // }

  liftMotor.move(0);
}

void Lift::holdLiftDown() {
  liftMotor.move(-20);
}