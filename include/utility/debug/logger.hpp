#include "api.h"
#include <iostream>
#include <fstream>

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

class Logger
{
private:
  std::ofstream fileWriter;

public:
  Logger(std::string fileURL);
  void writeFile(std::string head, std::string content);
  void writeFile(std::string content);
  void closeFile();
};

#endif