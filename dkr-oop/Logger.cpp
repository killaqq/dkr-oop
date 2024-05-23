#include "Logger.h"

#include <iostream>

Logger::Logger(const std::string& filename)
{
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open())
        std::cerr << "Failed to open log file!" << std::endl;
}

Logger::~Logger()
{
    if (logFile.is_open())
        logFile.close();
}

void Logger::log(const std::string& message)
{
    time_t now = time(0);
    char dt[64];
    ctime_s(dt, 64, &now);
    dt[strlen(dt) - 1] = '\0';
    logFile << "[" << dt << "] " << message << std::endl;
}
