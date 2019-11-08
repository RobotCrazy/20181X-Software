#include "api.h"
#include <vector>
#include "utility/intakeMovement.hpp"

#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

class Intake
{
private:
  pros::Motor intakeLeft;
  pros::Motor intakeRight;
  std::queue<IntakeMovement> movements;

public:
  Intake(int intakePortLeft, int intakePortRight);
  void driverControl();

  void runIntake(int ticks);

  void addMovement(IntakeMovement im);
  IntakeMovement getFirstMovement();
  void deleteFirstMovement();
  void completeMovements();

  void startIntake();
  void stopIntake();
};

extern void intakeTaskActions(void *param);
extern pros::Task intakeControl;

#endif