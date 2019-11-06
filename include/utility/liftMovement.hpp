#include "api.h"

#ifndef _LIFTMOVEMENT_HPP_
#define _LIFTMOVEMENT_HPP_

class LiftMovement
{
private:
  int targetPos;

public:
  static const int LIFT_MOVEMENT_DEPLOY;
  static const int LIFT_MOVEMENT_MOVEARM;

  std::vector<std::shared_ptr<Movement>> prereqMovements;
  LiftMovement();
  LiftMovement(int target);

  void setTargetPos(int target);
  int getTargetPos();
};

#endif