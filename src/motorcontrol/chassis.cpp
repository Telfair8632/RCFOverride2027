#include "haws/motorcontrol/chassis.h"
#include "haws/config.hpp"
#include "pros/llemu.hpp"

namespace chassis
{

void reset() {
    motor_left.tare_position_all();
    motor_right.tare_position_all();
}

void move(int lPower, int rPower) {
    motor_left.move(lPower * 1.27);
    motor_right.move(rPower * 1.27);
}

void brake(motor_brake_mode_e brakeMode) {
    motor_left.set_brake_mode_all(brakeMode);
    motor_right.set_brake_mode_all(brakeMode);
    motor_left.brake();
    motor_right.brake();
}

int getPosition() {
    std::vector<double> leftPositions = motor_left.get_position_all();
    std::vector<double> rightPositions = motor_right.get_position_all();

    int total = 0;
    int count = 0;
    for (int leftPos : leftPositions) {
        total += leftPos;
        count += 1;
    }
    for (int rightPos : rightPositions) {
        total += rightPos;
        count += 1;
    }
    return total / count;
}

void moveEnc(int distance, int timeout) {
    int current = 0;
    int sign = 1;
    float power = 0;
    int time = 0;
    // 记录符号，控制输出都以第一象限计算
    if (distance < 0) {
        sign = -1;
        distance = -distance;
    }

    reset();
    while (true) {
        // 更新当前编码器值
        current = abs(getPosition());

        // 退出条件判断
        if (distance - current <= 20 || time > timeout) {
            break;
        }

        // 计算输出功率
        if (current < distance / 2) {
            power = STRIGHT_MIN_V + fabs(sqrt(current * 2 * STRIGHT_ACC));
        } else {
            power = fabs(sqrt((distance - current) * 2 * STRIGHT_ACC));
        }
        power = CONSTRAIN(power, STRIGHT_MIN_V, STRIGHT_MAX_V);

        // 底盘输出
        move(power * sign, power * sign);

        pros::delay(15);
        time += 15;
    }

    brake();
    pros::lcd::print(7, "moveEnc: [%d / %d] %dms", current, distance, time);
}

}