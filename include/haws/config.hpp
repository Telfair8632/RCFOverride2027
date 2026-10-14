#include "api.h"
// #define DEBUG
using namespace pros;

#ifndef _HAWS_CONFIG_H_
#define _HAWS_CONFIG_H_
#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

#define master Controller(pros::E_CONTROLLER_MASTER)

const pros::MotorGroup motor_left({-15,-14,13});
const pros::MotorGroup motor_right({16,12,-11});

const pros::MotorGroup motor_lift({-8,9});
const pros::Motor motor_roller(-20);
const pros::Motor motor_arm(4);

const Imu sensor_gyro(18);   // 陀螺仪

const pros::adi::DigitalOut digit_clip('B', false);
#endif