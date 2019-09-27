#include "api.h"
#include <functional>
#include <list>
#include <memory>

#ifndef _PREREQ_HPP_
#define _PREREQ_HPP_

class Prereq
{
private:
  std::function<bool()> condition; //experiment with "auto condition"
  //std::list<std::shared_ptr<DriveMovement>> movements; //list of movements that must be completed

public:
  Prereq();
  Prereq(std::function<bool()> c);
  void setPrereqFunction(std::function<bool()> c);
  bool isComplete();
};

#endif