#include "main.h"

IntakeMovement::IntakeMovement(int targetPos)
{
  targetPosition = targetPos;
}

bool IntakeMovement::readyToOperate()
{
  return actionComplete;
}