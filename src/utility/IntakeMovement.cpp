#include "main.h"

IntakeMovement::IntakeMovement(int targetDegrees)
{
  degrees = targetDegrees;
}

void IntakeMovement::setDegrees(int targetDegrees)
{
  degrees = targetDegrees;
}

int IntakeMovement::getDegrees()
{
  return degrees;
}
