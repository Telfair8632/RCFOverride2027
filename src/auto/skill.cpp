#include "haws/auto.h"
#include "pros/motors.h"

void skill() {
    // 满功率走1157距离，超时时间1600ms
    chassis::moveEnc(1157, 1600);
    // 50功率走1157距离，超时时间1600ms
    chassis::moveEnc(1157, 1600, 50);
    // 50功率走1157距离，超时时间1600ms，结束后不刹车
    chassis::moveEnc(1157, 1600, 50, pros::E_MOTOR_BRAKE_INVALID);
}
