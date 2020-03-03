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
  bool deploySetUpRequested;
  pros::ADIAnalogIn intakeLineSensor;
  std::queue<IntakeMovement> movements;

public:
  Intake(int intakePortLeft, int intakePortRight, char intakeLineSensorPort);
  void driverControl();

  void runIntake(int ticks);

  void addMovement(IntakeMovement im);
  IntakeMovement getFirstMovement();
  void deleteFirstMovement();
  void completeMovements();

  void startIntake();
  void stopIntake();

  void reverseIntakeForDeploy(int ms = 350);
  void reverseIntakeForDeployAsync();
  void setDeploySetUpRequestedFalse();
  void reverseIntake(int ms, int speed = 127);
  
  void runIntakeAt(int speed);

  void runIntakeForAsync(int ticks);
};

extern void intakeTaskActions(void *param);
extern pros::Task intakeControl;

#endif