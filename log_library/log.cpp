#include "log.h"

Logger::Logger(const std::string& filename, LogLevel min_level)
    : min_log_level(min_level) {
    log_file.open(filename, std::ios::app);
    if (!log_file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл журнала!");
    }
}

Logger::~Logger() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    // функция записывает сообщение в журнал
    
    if (level < min_log_level) return;

    std::lock_guard<std::mutex> lock(log_mutex);
    
    log_file << "[" << getCurrentTime() << "] "
             << "[" << logLevelToString(level) << "] "
             << message << std::endl;
}

void Logger::setLogLevel(LogLevel new_level) {
    // функция устанавливает уровень логирования
    
    std::lock_guard<std::mutex> lock(log_mutex);
    min_log_level = new_level;
}

std::string Logger::getCurrentTime() {
    // функция возвращает текущее время
    
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&time);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Logger::logLevelToString(LogLevel level) {
    // функция переводит enum LogLevel в строку
    
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
