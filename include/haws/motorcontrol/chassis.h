#ifndef _HAWS_CHASSIS_H_
#define _HAWS_CHASSIS_H_

#include "api.h"

using namespace pros;

namespace chassis {
#define STRIGHT_ACC 4
#define STRIGHT_MAX_V 100
#define STRIGHT_MIN_V 25
#define TURN_ACC 10
#define TURN_MAX_V 100
#define TURN_MIN_V 20

/**
 * @brief 重置所有底盘电机编码器
 */
void reset();

/**
 * @brief 底盘控制基础函数
 * @param lPower 左边电机的功率值(-100至100)
 * @param rPower 右边电机的功率值(-100至100)
 */
void move(int lPower, int rPower);

/**
 * @brief 底盘刹车函数
 * @param brakeMode 拓展参数: 刹车模式(默认为brake)
 * @note 如不填入刹车模式, 使用brake模式进行刹车
 */
void brake(motor_brake_mode_e brakeMode = E_MOTOR_BRAKE_BRAKE);

/**
 * @brief 读取底盘编码器的值
 * @return 底盘编码器的值
 */
int getPosition();

/**
 * @brief 编码器控制底盘直行函数
 * @param distance  移动的距离(电机的编码器目标值, 正数为前进, 负数为后退)
 * @param timeout   超时时间，单位ms，超过此时长后退出控制循环
 * @param maxPower  拓展参数: 底盘移动的最大功率(默认为100, 可填入0至100的数值, 需为正数)
 * @param brakeMode 拓展参数: 移动至目标值后的刹车方式(默认为brake)
 */
void moveEnc(int distance, int timeout, int maxPower = STRIGHT_MAX_V, motor_brake_mode_e brakeMode = E_MOTOR_BRAKE_BRAKE);

/**
 * @brief 使用PID+陀螺仪控制底盘转向函数
 * @param angle     底盘朝向的角度值(陀螺仪相对初始位置的值)
 * @param timeout   超时时间，单位ms，超过此时长后退出控制循环
 * @param maxPower  拓展参数: 底盘移动的最大功率(默认为100, 可填入0至100的数值, 需为正数)
 */
void turnGyroPID(int angle, int timeout, int maxPower = TURN_MAX_V);

/**
 * @brief 使用陀螺仪控制底盘转向函数
 * @param angle     底盘朝向的角度值(陀螺仪相对初始位置的值)
 * @param timeout   超时时间，单位ms，超过此时长后退出控制循环
 * @param maxPower  拓展参数: 底盘移动的最大功率(默认为100, 可填入0至100的数值, 需为正数)
 * @param brakeMode 拓展参数: 移动至目标值后的刹车方式(默认为brake)
 */
void turnGyro(int angle, int timeout, int maxPower = TURN_MAX_V, motor_brake_mode_e brakeMode = E_MOTOR_BRAKE_BRAKE);

}
#endif
