#include "api.h"
// #define DEBUG
using namespace pros;

#ifndef _HAWS_CONFIG_H_
#define _HAWS_CONFIG_H_
#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

#define master Controller(pros::E_CONTROLLER_MASTER)

const pros::MotorGroup motor_left({-10,-2,8});
const pros::MotorGroup motor_right({6,7,-3});

const pros::MotorGroup motor_lift({13,-14});
const pros::Motor motor_roller(-18);
const pros::Motor motor_arm(11);

const Imu sensor_gyro(15);   // 陀螺仪

const pros::adi::DigitalOut digit_clip('A', true);
#endif