//
// Created by michi on 19.03.18.
//

#ifndef KILOTRACKER_LOGGER_H
#define KILOTRACKER_LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

class Logger {

public:
  Logger(std::string filename);
  ~Logger();

  void writeLine(std::string line);
  Logger& operator<<(const std::string& sMessage);
  Logger& operator<<(const int& sMessage);
  void flush();
private:
  std::ofstream file;
};

#endif //KILOTRACKER_LOGGER_H
