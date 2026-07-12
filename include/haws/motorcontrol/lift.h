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
 * @brief 设置升降抬升/下降的档位
 * @param gear 档位值(应在0至最大档位数值之间)
 * @note 升降会在设置档位后, 开启线程, 自动抬升/下降至对应的高度.
 *       当上一个线程正在运行时, 若设置新的档位, 会停止当前正在进行的进程, 抬升/下降至新的档位.
 *       该函数内部会保证变量的线程安全, 且会释放线程资源.
 */
void setGear(int gear);

/**
 * @brief 获取当前设置的档位
 * @return 返回当前的档位值
 */
int getGear();

/**
 * @brief 设置线程是否可执行
 */
void setTaskEnable(bool enable);
}
#endif
