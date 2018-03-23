//
// Created by michi on 19.03.18.
//



#include "Logger.h"

using std::string;
Logger::Logger(string filename) {

  file.open(filename);
}

void Logger::writeLine(string line) {
  file << line << std::endl;
}

void Logger::flush(){
  file.flush();
}

Logger& Logger::operator<<(const string& sMessage)
{
  file << sMessage;
  return *this;
}

Logger& Logger::operator<<(const int& iMessage)
{
  file << iMessage;
  return *this;
}

Logger::~Logger() {
  file.close();
}