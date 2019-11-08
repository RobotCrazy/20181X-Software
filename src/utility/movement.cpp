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

void Movement::setPrereqMovements(std::vector<std::shared_ptr<Movement>> actions)
{
  prereqMovements = actions;
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
