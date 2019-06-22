#include "main.h"

Prereq::Prereq()
{
}

Prereq::Prereq(std::function<bool()> c)
{
  condition = c;
  //This is sample syntax for a lambda:
  // auto lambda = []() { std::cout << "Code within a lambda expression" << std::endl; };
  // lambda();
}

void Prereq::setPrereqFunction(std::function<bool()> c)
{
  condition = c;
}

bool Prereq::isComplete()
{
  return (condition() == true);
}