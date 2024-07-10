#include "logger.h"

using namespace std;

int Logger::level = 5;

Logger::Logger(int _level){
  level = _level;
};

Logger::~Logger(void){
};

void outputTime(){
  time_t now = time(0);
  tm *ltm = localtime(&now);
  cout << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec;
}

void Logger::LogInfo(std::string message){
  outputTime();
  cout << " [INFO] " << message << endl;
};

void Logger::LogError(std::string message){
  outputTime();
  cout << " [ERROR] " << message << endl;
};

void Logger::LogDebug(std::string message){
  if (level < 5) {
    return;
  }
  outputTime();
  cout << " [DEBUG] " << message << endl;
}; 