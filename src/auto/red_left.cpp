#include "haws/auto.h"

using namespace chassis;
using namespace lift;

void redLeft1() {
    
    //撞杆两下
    lift::liftToPosition(950);
    // chassis::moveEnc(-300,3000);
    // delay(300);
    // chassis::moveEnc(340,3000);
    // chassis::moveEnc(-330,3000);
    // delay(300);
    // chassis::moveEnc(380,3000);

    //放预装
    chassis::moveEnc(960,3000);
    delay(100);
    turnGyro(-70,3000);
    delay(100);
    motor_arm.move(50);
    delay(470);
    motor_arm.move(0);
    chassis::moveEnc(625,3000);
    lift::liftToPosition(5);
    delay(1000);
    digit_clip.set_value(true);
    delay(500);

    // //后退取第一个桩夹住
    chassis::moveEnc(-250,3000);
    delay(100);
    //turnGyro(-70,3000);
    /*lift::lift(-100);
    delay(100);
    lift::lift(0);
    chassis::moveEnc(440,3000);
    chassis::moveEnc(400,3000,30);
    delay(200);
    digit_clip.set_value(false);
        //夹住后抬升再往前走一点
    lift::lift(100);
    delay(340);
    lift::lift(0); 
    chassis::moveEnc(300,3000);
    delay(200);

    //转向并放置桩
    turnGyro(140,3000);
    delay(100);
    chassis::moveEnc(450,3000);
    delay(100);
    motor_arm.move(50);
    delay(90);
    motor_arm.move(0);
    delay(100);

    // digit_clip.set_value(true);


    //chassis::moveEnc(1200,3000);
    
    //chassis::turnGyro(90,3000);
    */ 
}

void redLeft2() {
  
}