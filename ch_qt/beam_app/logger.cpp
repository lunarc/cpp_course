#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger::Logger()
    : currentLogLevel(LogLevel::INFO)
{
}

Logger::~Logger()
{
    if (logFile.is_open())
    {
        logFile.close();
    }
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level)
{
    currentLogLevel = level;
}

void Logger::setLogFile(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (logFile.is_open())
    {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
}

void Logger::log(LogLevel level, const std::string& message)
{
    if (level >= currentLogLevel)
    {
        std::lock_guard<std::mutex> lock(mtx);
        std::string timestamp = getCurrentTimestamp();
        std::string levelStr = getLevelString(level);

        std::stringstream ss;
        ss << timestamp << " [" << levelStr << "] " << message << std::endl;

        if (logFile.is_open())
        {
            logFile << ss.str();
            logFile.flush();
        }
        std::cout << ss.str();
    }
}

std::string Logger::getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto now_tm = std::localtime(&now_c);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now_tm);

    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch())
        % 1000;

    std::stringstream ss;
    ss << buffer << "." << std::setfill('0') << std::setw(3) << now_ms.count();
    return ss.str();
}

std::string Logger::getLevelString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG:
        return "DEBUG";
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}
