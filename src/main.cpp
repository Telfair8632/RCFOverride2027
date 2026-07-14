#include "main.h"
#include "haws/motorcontrol/lift.h"
#include "haws/motorcontrol/chassis.h"
#include "haws/auto.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	
    motor_left.set_brake_mode(E_MOTOR_BRAKE_COAST);
    motor_right.set_brake_mode(E_MOTOR_BRAKE_COAST);
    motor_lift.set_brake_mode_all(E_MOTOR_BRAKE_HOLD);
    motor_arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    chassis::move(0, 0);
    lift::setTaskEnable(false);
    pros::delay(10);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
int autoSelection = 1;
const char *autoTitles[] = {
    "技能",
    "红左1",
    "红左2",
    "红右1",
    "红右2",
    "蓝左1",
    "蓝左2",
    "蓝右1",
    "蓝右2"};
void autonomous() {
    switch (autoSelection) {
    case 0:
        skill();
        break;
    case 1:
        redLeft1();
        break;
    case 2:
        redLeft2();
        break;
    case 3:
        redRight1();
        break;
    case 4:
        redRight2();
        break;
    case 5:
        blueLeft1();
        break;
    case 6:
        blueLeft2();
        break;
    case 7:
        blueRight1();
        break;
    case 8:
        blueRight2();
        break;
    }
}

// 是否进入选自动程序
bool isSelectAuto = false;
// 选自动
void autoSelector() {
    master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
    while (isSelectAuto) {
    //     // TODO: 显示陀螺仪传感器的值
    //     // master.print(2, 20, "gyro:%.3f", gyro.get_rotation());
        if (master.get_digital_new_press(DIGITAL_LEFT)) {
            autoSelection = CONSTRAIN(autoSelection - 1, 0, 8);
            master.clear_line(2);
            pros::delay(50);
            master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
        }
        if (master.get_digital_new_press(DIGITAL_RIGHT)) {
            autoSelection = CONSTRAIN(autoSelection + 1, 0, 8);
            master.clear_line(2);
            pros::delay(50);
            master.print(2, 0, "[ ]%s", autoTitles[autoSelection]);
        }
        if (master.get_digital_new_press(DIGITAL_B)) {
            master.print(2, 1, "x");
            pros::delay(800);
            master.clear_line(2);
            break;
        }
        pros::delay(50);
    }
    pros::delay(50);
    isSelectAuto = false;
}

/*
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    bool clipState = true;
    int curLiftGear = 0;

    autoSelector();

	while(true) {
        pros::lcd::print(6, "enc: %d", chassis::getPosition()); 
        pros::lcd::register_btn1_cb(chassis::reset); 
		int ch3 = master.get_analog(ANALOG_LEFT_Y);
		int ch1 =master.get_analog(ANALOG_RIGHT_X);
        bool L1 = master.get_digital(DIGITAL_L1);
        bool L2 = master.get_digital(DIGITAL_L2);
        bool R1 = master.get_digital_new_press(DIGITAL_R1);
        bool R2 = master.get_digital(DIGITAL_R2);
        bool btnU = master.get_digital_new_press(DIGITAL_UP);
        bool btnD = master.get_digital_new_press(DIGITAL_DOWN);
        bool btnA = master.get_digital(DIGITAL_A);
        bool btnB = master.get_digital(DIGITAL_B);
        
		chassis::move(ch3 + ch1, ch3 - ch1);
        
        // 升降
        if (L1) {
            lift::lift(100);
        } else if (L2) {
            lift::lift(-100);
        } else {
            lift::lift(0);
        }
        if (btnU) {
            lift::setGear(CONSTRAIN(lift::getGear() + 1, 0, 4));
        }
        if (btnD) {
            lift::setGear(CONSTRAIN(lift::getGear() - 1, 0, 4));
        }


        // 小手
        if (btnA) {
            motor_arm.move(50);
        } else if (btnB) {
            motor_arm.move(-50);
        } else {
            motor_arm.brake();
        }


        // 夹子
        if (R1) {
            clipState = !clipState;
            digit_clip.set_value(clipState);
        }
        

        // 滚轮
        if (R2) {
            motor_roller.move(127);
        } else {
            motor_roller.move(0);
        }

		pros::delay(30);
	}
}
	

