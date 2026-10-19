#ifndef _HAWS_LOGGER_H_
#define _HAWS_LOGGER_H_

#include <cstddef>
#include <string>
#include <vector>
#include "haws/config.hpp"

using namespace std;
using namespace pros;

using FunctionPtr = void(*)();
#define MAX_LOG_COUNT 6 // TOTAL LINE: 8

class Logger {
public:
    Logger(const Logger&) = delete; // 禁用拷贝构造
    Logger& operator=(const Logger&) = delete; // 禁用赋值构造
    static Logger& getInstance(); // 单例获取函数

    Logger(); // 构造函数
    ~Logger(); // 析构函数

    void resetTimer();
    // 主控清屏
    void clear();
    // 打印日志（带参数）
    void info(const char* format, ...);
    // 打印日志
    void info(string content);
    // 向上翻页
    void pageUp();
    // 向下翻页
    void pageDown();
    // 向上翻页（静态函数，用于注册按键回调）
    static void pageUpCallback();
    // 向下翻页（静态函数，用于注册按键回调）
    static void pageDownCallback();

private:
    // 刷新显示
    void refresh();
    // 获取时间戳
    string getTimeStr();
    // 添加日志至日志列表，长日志分行
    void append(string content);

    // 日志列表
    vector<string> logList;
    // 锁
    Mutex logListMutex;
    // 当前显示的第一行对应的日志列表角标
    std::size_t current; 
    // 计时器
    int32_t timer;
};


#endif