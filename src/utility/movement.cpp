#include "main.h"

Movement::Movement()
{
}

void Movement::setComplete()
{
  actionComplete = true;
}

bool Movement::isComplete()
{
  return actionComplete;
}

bool Movement::readyToOperate()
{
  for (int i = 0; i < prereqMovements.size(); i++)
  {
    if (prereqMovements.at(i).get()->isComplete() == false)
    {
      return false;
    }
  }
  return true;
}