#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "../log_library/log.h"

std::queue<std::pair<std::string, LogLevel>> log_queue;
std::mutex queue_mutex;
std::condition_variable queue_cv;
bool running = true;

void logWorker(std::shared_ptr<Logger> logger) {
    while (running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [] { return !log_queue.empty() || !running; });

        while (!log_queue.empty()) {
            auto [message, level] = log_queue.front();
            log_queue.pop();
            lock.unlock();
            
            logger->log(message, level);

            lock.lock();
        }
    }
}

LogLevel parseLogLevel(const std::string& level_str) {
    if (level_str == "INFO") return LogLevel::INFO;
    if (level_str == "WARNING") return LogLevel::WARNING;
    if (level_str == "ERROR") return LogLevel::ERROR;
    return LogLevel::INFO;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Использование: " << argv[0] << " <log_file> <log_level>\n";
        return 1;
    }

    std::string log_file = argv[1];
    LogLevel default_level = parseLogLevel(argv[2]);

    auto logger = std::make_shared<Logger>(log_file, default_level);
    std::thread worker(logWorker, logger);

    std::string message;
    while (true) {
        std::cout << "Введите сообщение (или 'exit' для выхода): ";
        std::getline(std::cin, message);
        
        if (message == "exit") {
            break;
        }

        std::string level_str;
        std::cout << "Введите уровень важности (INFO, WARNING, ERROR) [по умолчанию]: ";
        std::getline(std::cin, level_str);

        LogLevel level = level_str.empty() ? default_level : parseLogLevel(level_str);

        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            log_queue.push({message, level});
        }
        queue_cv.notify_one();
    }

    running = false;
    queue_cv.notify_one();
    worker.join();

    return 0;
}
