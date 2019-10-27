#include "api.h"
#include <vector>
#include "utility/intakeMovement.hpp"

#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

class Intake
{
private:
  pros::Motor intake;
  std::queue<IntakeMovement> movements;

public:
  Intake(int intakePort);
  void driverControl();

  void runIntake(int ticks);

  void addMovement(IntakeMovement im);
  IntakeMovement getFirstMovement();
  void deleteFirstMovement();
  void completeMovements();
};

extern void intakeTaskActions(void *param);
extern pros::Task intakeControl;

#endif