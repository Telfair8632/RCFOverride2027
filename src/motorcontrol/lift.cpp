#include "haws/motorcontrol/lift.h"
#include "haws/config.hpp"
#include "main.h"

namespace lift
{
void liftToGear(void *liftTask);
bool getTaskEnable();

Mutex liftGearMutex; // 互斥锁
int liftGear = 0;    // 当前档位
Mutex taskEnableMutex;   // 互斥锁
bool taskEnable = false; // 是否允许执行进程
Task autoLift = Task(liftToGear); // 切换档位进程

const int position[] = {
    5, 
    950, 
    1550,
    2200,
    2740};

void lift(int power, motor_brake_mode_e brakeMode) {
    if (power == 0) {
        motor_lift.set_brake_mode_all(brakeMode);
        motor_lift.brake();
    } else {
        if (getTaskEnable()) {
            pros::lcd::print(2, "lift power != 0");
            setTaskEnable(false);
            pros::delay(10);
            // autoLift.remove();
        }
        motor_lift.move(power * 1.27);
    }
}

void setTaskEnable(bool enable) {
    taskEnableMutex.take(100);
    taskEnable = enable;
    taskEnableMutex.give();
}

bool getTaskEnable() {
    taskEnableMutex.take(100);
    bool res = taskEnable;
    taskEnableMutex.give();
    return res;
}

int getGear() {
    liftGearMutex.take(100);
    int res = liftGear;
    liftGearMutex.give();
    return res;
}

void liftToGear(void *liftTask) {
    int curGear = getGear();
    int target = position[curGear];
    while (getTaskEnable()) {
        // 计算误差
        int err = target - motor_lift.get_position();
        int power = (err / abs(err)) * 40;

        // 退出
        if (abs(err) < 5) {
            lift(0);
            setTaskEnable(false);
            break;
        }

        motor_lift.move(power * 1.27);
        pros::delay(10);
    }
    // logger::log("liftToGear: tar=" + std::to_string(target) + ", pos=" + std::to_string(armRotation.get_position()));
    pros::lcd::print(1, "liftToGear %d, %.2f/%d", getGear(), motor_lift.get_position(), target);
}

void setGear(int gear) {
    // 只有在设置的档位与当前不同时有效
    if (gear != getGear()) {
        // 设置新的档位值
        pros::lcd::print(0, "set gear: %d", gear);    
        // logger::log("set gear: " + std::to_string(gear));
        liftGearMutex.take(100);
        liftGear = gear;
        liftGearMutex.give();
        // 若当前有线程正在运行, 释放资源
        if (getTaskEnable()) {
            setTaskEnable(false);
            pros::delay(10);
            // autoLift.remove();
        }
        // 开启新的线程执行换档
        setTaskEnable(true);
        pros::delay(10);
        autoLift = Task(liftToGear);
    }
}

}