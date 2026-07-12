#include "haws/motorcontrol/chassis.h"
#include "haws/config.hpp"

namespace chassis
{

void reset() {
    motor_left.tare_position();
    motor_right.tare_position();
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

}