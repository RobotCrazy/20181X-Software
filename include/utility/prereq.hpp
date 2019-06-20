#include "api.h"
#include <functional>

#ifndef _PREREQ_HPP_
#define _PREREQ_HPP_

class Prereq
{
private:
  std::function<bool()> condition; //experiment with "auto condition"

public:
  Prereq();
  Prereq(std::function<bool()> c);
  void setPrereqFunction(std::function<bool()> c);
  bool isComplete();
};

#endif