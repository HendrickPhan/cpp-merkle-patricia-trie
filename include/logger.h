#pragma once
#include <iostream>

class Logger {
public:

  Logger(int _level);
  ~Logger(void);
  static int level;
  static void Log(std::string message);
  static void LogInfo(std::string message);
  static void LogError(std::string message);
  static void LogDebug(std::string message);
};
