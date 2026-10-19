#ifndef _HAWS_LIFT_H_
#define _HAWS_LIFT_H_

#include "api.h"

using namespace pros;

namespace lift {

/**
 * @brief 控制升降
 * @param power 电机功率
 */
void lift(int power, motor_brake_mode_e brakeMode = E_MOTOR_BRAKE_HOLD);

/**
 * @brief 手动升降优化
 * @param power 电机功率
 */
void lift_S(int power);

/**
 * @brief 设置线程是否可执行
 */
void setTaskEnable(bool enable);

/**
 * @brief 升降只旋转传感器指定位置
 * @param position 目标高度值
 * @param isAsync 是否开启线程异步执行, true为开启线程, 默认为true
 */
void liftToPosition(int position, bool isAsync = true);
}
#endif
