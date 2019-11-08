#include "api.h"

#ifndef _INTAKE_MOVEMENT_HPP_
#define _INTAKE_MOVEMENT_HPP_

class IntakeMovement : public Movement
{
private:
  int degrees;

public:
  IntakeMovement(int targetDegrees);
  void setDegrees(int targetDegrees);
  int getDegrees();
};

#endif