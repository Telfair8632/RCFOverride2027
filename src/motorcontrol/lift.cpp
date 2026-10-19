#include "haws/motorcontrol/lift.h"
#include "haws/config.hpp"
#include "haws/display/logger.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

namespace lift
{
void liftToTarget(void *liftTask);
bool getTaskEnable();
void setTargetPosition(int target);
int getTargetPosition();

Mutex taskEnableMutex;   // 互斥锁
bool taskEnable = false; // 是否允许执行进程
Mutex isRunningLiftMutex;   // 互斥锁
bool isRunningLift = false; // 是否正在执行升降部分
Mutex targetPositionMutex; // 互斥锁
int targetPosition = 0;    // 摇臂抬升目标角度值

Task autoLift = Task(liftToTarget); // 升降进程

const int position[] = {
    5, 
    950,
    2550,
    5000,
    7740};

void lift(int power, motor_brake_mode_e brakeMode) {
    if (power == 0) {
        motor_group_lift.set_brake_mode_all(brakeMode);
        motor_group_lift.brake();
    } else {
        motor_group_lift.move(power * 1.27);
    }
}

void lift_S(int power) {
    static bool isRamp = false;
    static int rampTime = 300;
    static int32_t rampStartTime = 0;

    if (abs(power) > 25) {
        motor_group_lift.move(power);
        isRamp = false;
    } else {
        if (!isRamp) {
            isRamp = true;
            rampStartTime = pros::millis();
        }
        int32_t elapsed = pros::millis() - rampStartTime;
        if (elapsed < rampTime) {
            lift(0, E_MOTOR_BRAKE_BRAKE);
        } else {
            lift(0, E_MOTOR_BRAKE_HOLD);
        }
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

void setTargetPosition(int target) {
    targetPositionMutex.take(100);
    targetPosition = target;
    targetPositionMutex.give();
}

int getTargetPosition() {
    targetPositionMutex.take(100);
    int target = targetPosition;
    targetPositionMutex.give();
    return target;
}

void setIsRunningLift(bool isRunning) {
    isRunningLiftMutex.take(100);
    isRunningLift = isRunning;
    isRunningLiftMutex.give();
}

bool getIsRunningLift() {
    isRunningLiftMutex.take(100);
    bool res = isRunningLift;
    isRunningLiftMutex.give();
    return res;
}

void liftToTarget(void *liftTask) {
    int target = getTargetPosition();
    int err = target - sensor_lift.get_position();
    bool sign = err > 0;
    uint32_t start_time = pros::millis();
    while (getTaskEnable()) {
        // 计算误差
        err = target - sensor_lift.get_position();

        // 退出
        if ((sign && err < 200) ||
            (!sign && err > -200) ||
            pros::millis() - start_time > 2000) {
            motor_group_lift.move(0);
            setIsRunningLift(false);
            break;
        }

        motor_group_lift.move(CONSTRAIN(err * 0.35, -30, 65));
        pros::delay(10);
    }
    // pros::lcd::print(1, "liftToTarget %d/%d", sensor_lift.get_position(), target);
    Logger::getInstance().info("liftToTarget %d/%d", sensor_lift.get_position(), target);
    Logger::getInstance().info("lift brake");
    start_time = pros::millis();
    while (getTaskEnable()) {
        int32_t elapsed = pros::millis() - start_time;
        if (elapsed <= 100) {
            lift(0, E_MOTOR_BRAKE_BRAKE);
        } else {
            // break;
            lift(0, E_MOTOR_BRAKE_HOLD);
        }
        pros::delay(20);
    }
}

void liftToPosition(int position, bool isAsync) {
    setTargetPosition(position);
    // 若当前有线程正在运行, 释放资源
    if (getTaskEnable()) {
        setTaskEnable(false);
        pros::delay(20);
        // autoLift.remove();
    }
    setTaskEnable(true);
    setIsRunningLift(true);
    autoLift = Task(liftToTarget);
    if (!isAsync) {
        while (getIsRunningLift()) {
            pros::delay(20);
        }
    }
}

}