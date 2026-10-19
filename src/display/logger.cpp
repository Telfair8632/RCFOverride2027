#include "haws/display/logger.h"
#include "pros/rtos.hpp"
// #include "liblvgl/llemu.hpp"
// #include "pros/llemu.hpp"
// #include <cstddef>
// #include <iomanip>

Logger::Logger() {
    this->logList.clear();
    this->current = 0;
    this->timer = pros::millis();
}

Logger::~Logger() {}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::resetTimer() {
    this->timer = pros::millis();
}

void Logger::clear() {
    for (int i = 0; i < 8; i++) {
        lcd::clear_line(i);
    }
}

void Logger::refresh() {
    this->logListMutex.take(200);
    int size = logList.size();
    for (int i = 0; i < (min(size, MAX_LOG_COUNT)); i++) {
        lcd::print(i, logList.at(current + i).c_str());
    }
    this->logListMutex.give();
}

void Logger::pageUp() {
    current = CONSTRAIN(current - 1, 0, current);
}

void Logger::pageDown() {
    size_t size = logList.size();
    if (size <= MAX_LOG_COUNT) {
        current = 0;
    } else {
        current = CONSTRAIN(current + 1, current, size - MAX_LOG_COUNT);
    }
}

void Logger::pageUpCallback() {
    Logger::getInstance().pageUp();
    Logger::getInstance().refresh();
}

void Logger::pageDownCallback() {
    Logger::getInstance().pageDown();
    Logger::getInstance().refresh();
}

void Logger::append(string content) {
    string timeStr = getTimeStr();
    // 单行日志
    if (content.length() < 30) {
        logListMutex.take(500);
        logList.push_back(timeStr + content);
        int size = logList.size();
        current = max((size - MAX_LOG_COUNT), 0);
        logListMutex.give();
        return;
    }
    // 多行日志
    logListMutex.take(500);
    // 第一行加时间
    string firstLine = content.substr(0, 30);
    logList.push_back(timeStr + firstLine);
    // 中间行
    while (content.length() > 30) {
        content = content.substr(30);
        string line = content.substr(0, 30);
        logList.push_back("[----] " + line);
    }
    // 更新current
    int size = logList.size();
    current = max((size - MAX_LOG_COUNT), 0);
    logListMutex.give();
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    string content = "";

    // 按格式解析日志内容
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'b': {
                    bool value = va_arg(args, int);
                    content += (value ? "true" : "false");
                    break;
                }
                case 'd': {
                    int value = va_arg(args, int);
                    content += std::to_string(value);
                    break;
                }
                case 'f': {
                    float value = va_arg(args, double);
                    std::ostringstream stream;
                    stream << std::fixed << std::setprecision(2) << value;
                    content += stream.str();
                    break;
                }
                case 's': {
                    char* value = va_arg(args, char *);
                    content += value;
                    break;
                }
                default: {
                    content += '%';
                }
            }
        } else {
            content += *format;
        }
        format++;
    }
    va_end(args);

    this->append(content);
    this->refresh();
}

void Logger::info(string content) {
    this->append(content);
    this->refresh();
}

string Logger::getTimeStr() {
    int32_t current = pros::millis();
    float time = (current - timer) / 1000.0;
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(1) << time;
    string timeStr = stream.str();
    if (timeStr.length() == 3) {
        return "[0" + timeStr + "] ";
    }
    return "[" + timeStr + "] ";
}
