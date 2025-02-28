#include "../log_library/log.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cassert>


std::string getFileContent(const std::string& filename) {
    // функция возвращает текст из файла
    
    std::ifstream file(filename);
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    return content;
}

void testLogInfoMessage() {
    std::string log_filename = "test.log";
    Logger logger(log_filename, LogLevel::INFO);
    logger.log("Test info message", LogLevel::INFO);
    std::string content = getFileContent(log_filename);
    assert(content.find("Test info message") != std::string::npos);
    assert(content.find("INFO") != std::string::npos);
    std::remove(log_filename.c_str());
    std::cout << "testLogInfoMessage прошел успешно" << std::endl;
}


void testLogWarningMessage() {
    std::string log_filename = "test.log";
    Logger logger(log_filename, LogLevel::INFO);
    logger.log("Test warning message", LogLevel::WARNING);
    std::string content = getFileContent(log_filename);
    assert(content.find("Test warning message") != std::string::npos);
    assert(content.find("WARNING") != std::string::npos);
    std::remove(log_filename.c_str());
    std::cout << "testLogWarningMessage прошел успешно" << std::endl;

}

void testLogErrorMessage() {
    std::string log_filename = "test.log";
    Logger logger(log_filename, LogLevel::INFO);
    logger.log("Test error message", LogLevel::ERROR);
    std::string content = getFileContent(log_filename);
    assert(content.find("Test error message") != std::string::npos);
    assert(content.find("ERROR") != std::string::npos);
    std::remove(log_filename.c_str());
    std::cout << "testLogErrorMessage прошел успешно" << std::endl;

}

void testLogLevelFiltering() {
     std::string log_filename = "test.log";
    Logger logger(log_filename, LogLevel::WARNING);
    logger.log("Test info message (should be filtered)", LogLevel::INFO);
    logger.log("Test warning message", LogLevel::WARNING);
    std::string content = getFileContent(log_filename);
    assert(content.find("Test info message (should be filtered)") == std::string::npos);
    assert(content.find("Test warning message") != std::string::npos);
    std::remove(log_filename.c_str());
    std::cout << "testLogLevelFiltering прошел успешно" << std::endl;
}


void testMultipleLogMessages() {
    std::string log_filename = "test.log";
    Logger logger(log_filename, LogLevel::INFO);
    logger.log("Message 1", LogLevel::INFO);
    logger.log("Message 2", LogLevel::WARNING);
    logger.log("Message 3", LogLevel::ERROR);
    std::string content = getFileContent(log_filename);
    assert(content.find("Message 1") != std::string::npos);
    assert(content.find("Message 2") != std::string::npos);
    assert(content.find("Message 3") != std::string::npos);
    std::remove(log_filename.c_str());
    std::cout << "testMultipleLogMessages прошел успешно" << std::endl;
}




int main() {
    testLogInfoMessage();
    testLogWarningMessage();
    testLogErrorMessage();
    testLogLevelFiltering();
    testMultipleLogMessages();

    return 0;
}
