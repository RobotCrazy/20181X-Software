#include "main.h"

IntakeMovement::IntakeMovement(int targetPos)
{
  targetPosition = targetPos;
}

void IntakeMovement::setComplete()
{
  actionComplete = true;
}

bool IntakeMovement::isComplete()
{
  return actionComplete;
}

void IntakeMovement::setIntakePrereq(Prereq p)
{
  intakePrereq = p;
}

bool IntakeMovement::readyToOperate()
{
  return intakePrereq.isComplete();
}