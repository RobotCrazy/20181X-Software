#include "main.h"
#include "logger.hpp"

Logger::Logger(std::string fileURL) : fileWriter(fileURL)
{
}

void Logger::writeFile(std::string head, std::string content)
{
  fileWriter << head << ": " << content << std::endl;
}

void Logger::writeFile(std::string content)
{
  fileWriter << content << std::endl;
}

void Logger::closeFile()
{
  fileWriter.close();
}