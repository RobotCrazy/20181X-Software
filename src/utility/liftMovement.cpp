#include "main.h"

LiftMovement::LiftMovement()
{
}

LiftMovement::LiftMovement(int target)
{
  targetPos = target;
}

void LiftMovement::setTargetPos(int target)
{
  targetPos = target;
}

int LiftMovement::getTargetPos()
{
  return targetPos;
}