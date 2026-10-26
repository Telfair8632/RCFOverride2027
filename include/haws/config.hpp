#include "api.h"
// #define DEBUG
using namespace pros;

#ifndef _HAWS_CONFIG_H_
#define _HAWS_CONFIG_H_
#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

#define controller Controller(pros::E_CONTROLLER_MASTER)

const pros::MotorGroup motor_group_left({-17,-15,14});
const pros::MotorGroup motor_group_right({19,-16,20});

const pros::MotorGroup motor_group_lift({3,-4});
const pros::MotorGroup motor_group_roller({5,-10});
const pros::Motor motor_clip(-7);
const pros::Motor motor_toggle(6);

const Imu sensor_gyro(18);   // 陀螺仪
const Rotation sensor_lift(-2);  // 旋转 -- 升降

const pros::adi::DigitalOut pneumatic_b('B', false); // 气动 -- B口, 上电默认低电平(收回)


#endif