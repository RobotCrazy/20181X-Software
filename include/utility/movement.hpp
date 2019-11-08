#include "api.h"

#ifndef _MOVEMENT_HPP_
#define _MOVEMENT_HPP_

class Movement
{
protected:
  bool actionComplete = false;
  std::vector<std::shared_ptr<Movement>> prereqMovements;

public:
  Movement();
  void setComplete();
  bool isComplete();

  void setPrereqMovements(std::vector<std::shared_ptr<Movement>> actions);

  bool readyToOperate();
};

#endif