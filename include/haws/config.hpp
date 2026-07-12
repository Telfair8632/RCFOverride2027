#include "api.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/adi.h"

using namespace pros;
using namespace lemlib;

#ifndef _HAWS_CONFIG_H_
#define _HAWS_CONFIG_H_
#define CONSTRAIN(x, lower, upper) ((x)<(lower)?(lower):((x)>(upper)?(upper):(x)))
// 遥控器
#define controller Controller(pros::E_CONTROLLER_MASTER)

// 底盘电机端口定义
#define PORT_MOTOR_LEFT1 -13
#define PORT_MOTOR_LEFT2 -19
#define PORT_MOTOR_LEFT3 14
#define PORT_MOTOR_RIGHT1 18
#define PORT_MOTOR_RIGHT2 17
#define PORT_MOTOR_RIGHT3 -16

// 底盘电机齿轮组定义
#define CHASSIS_MOTOR_GEAR_SET pros::MotorGearset::blue//pros::MotorGear::blue

// 底盘控制方式
// #define CHASSIS_CONTROL_TANK
// #define CHASSIS_CONTROL_ARCADE_ONE
#define CHASSIS_CONTROL_ARCADE_TWO

// 陀螺仪端口定义
#define PORT_SENSOR_IMU 11

// 定位轮角度传感器端口定义
#define PORT_SENSOR_ENC_VERTICAL 15
#define PORT_SENSOR_ENC_HORIZONTAL 12

// 底盘外其他电机定义
const Motor motor_roller(7, MotorGear::blue); //intake motor
const Motor motor_upperSorter(-6 MotorGear::green); // motor 5.5w right
const Motor motor_lowerSorter(10, MotorGear::green); // motor 5.5w left

#define sensor_color Optical(8)   // 颜色传感器
#define sensor_dis Distance(2)

// 气缸端口定义
const adi::DigitalOut digit_upperdescore('A',LOW);
const adi::DigitalOut digit_loaderArm('G',HIGH);
#endif