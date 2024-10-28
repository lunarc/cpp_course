#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>
#include <string>

class Logger
{
public:
    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    static Logger& getInstance();

    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void setLogLevel(LogLevel level);
    void setLogFile(const std::string& filename);

    void log(LogLevel level, const std::string& message);

private:
    Logger();
    ~Logger();

    std::string getCurrentTimestamp();
    std::string getLevelString(LogLevel level);

    LogLevel currentLogLevel;
    std::ofstream logFile;
    std::mutex mtx;
};

#endif // LOGGER_H
