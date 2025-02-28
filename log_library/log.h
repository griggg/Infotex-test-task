#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <chrono>
#include <iomanip>

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
public:
    Logger(const std::string& filename, LogLevel min_level);
    ~Logger();
    
    void log(const std::string& message, LogLevel level);
    void setLogLevel(LogLevel new_level);

private:
    std::ofstream log_file;
    LogLevel min_log_level;
    std::mutex log_mutex;
    
    std::string getCurrentTime();
    std::string logLevelToString(LogLevel level);
};

#endif // LOG_H
