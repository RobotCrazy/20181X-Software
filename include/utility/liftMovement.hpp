#include "api.h"
#include "movement.hpp"

#ifndef _LIFTMOVEMENT_HPP_
#define _LIFTMOVEMENT_HPP_

class LiftMovement : public Movement
{
private:
  int targetPos;

public:
  static const int LIFT_MOVEMENT_DEPLOY = 1;
  static const int LIFT_MOVEMENT_MOVEARM = 2;

  LiftMovement();
  LiftMovement(int target);

  void setTargetPos(int target);
  int getTargetPos();
};

#endif