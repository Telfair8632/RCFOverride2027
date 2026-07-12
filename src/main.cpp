#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {

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
void opcontrol(){
	
	//mouth.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
    
    pros::MotorGroup left_mg({-1,-3,21});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({2,7,-5});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::MotorGroup arm({-8,9});//升降
	pros::Motor mouth(-12);//夹子翻转
    //pros::Motor abc(2);
   pros::adi::DigitalOut push('B');
    int pushS=1;
    pros::adi::DigitalOut pusha('C');
    int pushaS=0;
    
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	mouth.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while(true){
		int dir=master.get_analog(ANALOG_LEFT_Y);
		int turn=master.get_analog(ANALOG_RIGHT_X);
        
		left_mg.move(dir+turn);
		right_mg.move(dir-turn);
        
		if(master.get_digital(DIGITAL_L1)){
			arm.move(55);
		}else if(master.get_digital(DIGITAL_L2)){
			arm.move(-55);
		}else{
			arm.move(0);
			arm.brake();
		}
        if(master.get_digital(DIGITAL_A)){
			mouth.move(100);
            pros::delay(50); 
            mouth.move(0);
		}else if(master.get_digital(DIGITAL_B)){
			mouth.move(-55);
		}else{
			mouth.move(0);
			mouth.brake();
		}
       if(master.get_digital_new_press(DIGITAL_R1)){
            pushS=1-pushS;
            push.set_value(pushS);
            }
        if(master.get_digital_new_press(DIGITAL_R2)){
            pushaS=1-pushaS;
            pusha.set_value(pushaS);
            }
		

		pros::delay(30);
	}
	}                          // Run for 20 ms then update
	

