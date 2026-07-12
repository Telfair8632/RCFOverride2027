#ifndef _HAWS_CHASSIS_H_
#define _HAWS_CHASSIS_H_

#include "api.h"

using namespace pros;

namespace chassis {
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

}
#endif
