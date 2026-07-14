#include "haws/motorcontrol/chassis.h"
#include "haws/config.hpp"
#include "pros/colors.h"
#include "pros/colors.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "haws/motorcontrol/pid.h"
#include "pros/rtos.hpp"
#include "pros/screen.hpp"

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

void moveEnc(int distance, int timeout, int maxPower, motor_brake_mode_e brakeMode) {
    int current = 0;
    int sign = 1;
    float power = 0;
    uint32_t start_time = pros::millis();
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
        if (distance - current <= 20 || pros::millis() - start_time > timeout) {
            break;
        }

        // 计算输出功率
        if (current < distance / 2) {
            power = STRIGHT_MIN_V + fabs(sqrt(current * 2 * STRIGHT_ACC));
        } else {
            power = fabs(sqrt((distance - current) * 2 * STRIGHT_ACC));
        }
        power = CONSTRAIN(power, STRIGHT_MIN_V, maxPower);

        // 底盘输出
        move(power * sign, power * sign);

        pros::delay(15);
    }

    if (brakeMode != pros::E_MOTOR_BRAKE_INVALID) {
        brake(brakeMode);
    }
    pros::lcd::print(7, "moveEnc: [%d / %d] %dms", current, distance, pros::millis() - start_time);
}

void turnGyro(int angle, int timeout, int maxPower) {
    double kp = 1.0;
    double ki = 0.03; // 0.03
    double kd = 1.0; // 4.3
    PID pid = PID(kp, ki, kd);

    pid.SetTarget(angle);
    pid.SetIntegralMax(10);
    pid.SetIntegralRange(10);

    pid.SetSmallBigErrorTolerance(1, 3);
    pid.SetSmallBigErrorDuration(50, 250);
    pid.SetDerivativeTolerance(4.5);

    // Draw the baseline.
      double draw_amplifier = 230.0 / abs(angle);
      pros::screen::set_eraser(Color::black);
      pros::screen::erase();
      pros::screen::set_pen(Color::white);
      pros::screen::draw_line(0, abs(angle) * draw_amplifier,
                            600, abs(angle) * draw_amplifier);
      pros::screen::set_pen(Color::blue);

    // Start the PID loop.
    uint32_t start_time = pros::millis();
    double output;
    double current;
    double last = 0;
    int index = 1; // for draw line
    while (true) {
        // 更新当前陀螺仪值
        current = sensor_gyro.get_rotation();

        // 退出条件判断
        if (pid.TargetArrived() || pros::millis() - start_time > timeout) {
            break;
        }

        // 计算输出功率
        output = pid.Update(current);
        last = current;

        // Draw line
        pros::screen::draw_line(
            index * 3, fabs(last) * draw_amplifier,
            (index + 1) * 3, fabs(current * draw_amplifier));
        index++;
        
        // 底盘输出
        move(CONSTRAIN(output, -maxPower, maxPower),
             CONSTRAIN(-output, -maxPower, maxPower));

        pros::delay(10);
    }
    brake(pros::E_MOTOR_BRAKE_HOLD);
    pros::lcd::print(7, "turnGyro: [%.2f / %d] %dms", current, angle, pros::millis() - start_time);
}

}