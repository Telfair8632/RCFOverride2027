#include "api.h"
// #define DEBUG
using namespace pros;

#ifndef _HAWS_CONFIG_H_
#define _HAWS_CONFIG_H_
#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))

#define master Controller(pros::E_CONTROLLER_MASTER)

const pros::MotorGroup motor_left({-8,-13,10});
const pros::MotorGroup motor_right({15,19,-9});

const pros::MotorGroup motor_lift({11,-18});
const pros::Motor motor_roller(-14);
const pros::Motor motor_arm(3);

const Imu sensor_gyro(0);   // 陀螺仪

const pros::adi::DigitalOut digit_clip('A', true);
#endif