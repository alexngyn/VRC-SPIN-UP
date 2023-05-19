/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorLf              motor         1               
// MotorLm              motor         2               
// MotorLb              motor         3               
// MotorRf              motor         4               
// MotorRm              motor         5               
// MotorRb              motor         6               
// GPS                  gps           7               
// Controller1          controller                    
// intake               motor         8               
// shoot                motor         9               
// indexer              digital_out   A               
// expansion            digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_drivetrain.h"
#include <cmath>

using namespace vex;

competition Competition;

void clr_screen(void) {
  Brain.Screen.setFont(prop60);
  Brain.Screen.setFillColor(black);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(2,6);
  Brain.Screen.print("76209M");
  Brain.Screen.setCursor(3,8);
  Brain.Screen.print("IMF");
};

void arcade_drive(double x, double y){
  double maximum; 
  if (fabs(x) > fabs(y)) { maximum = fabs(x); } else { maximum = fabs(y); }
  double total = x + y, difference = y - x;
  if (y >= 0){
    if (x >= 0) {
      leftDrive.setVelocity(maximum, percent);
      rightDrive.setVelocity(difference, percent);
    } else {
      leftDrive.setVelocity(total, percent);
      rightDrive.setVelocity(maximum, percent);
    }
  } else {
    if (x >= 0){
      leftDrive.setVelocity(total, percent);
      rightDrive.setVelocity(-maximum, percent);
    } else {
      leftDrive.setVelocity(-maximum, percent);
      rightDrive.setVelocity(difference, percent);
    }
  }
}

void pre_auton(void) {
  vexcodeInit();
  clr_screen();
}

void pre_userc(void) {
  clr_screen();
  intake.spin(forward);
  shoot.spin(forward);
  rightDrive.spin(forward);
  leftDrive.spin(forward);
  MotorRb.spin(forward);
  intake.setVelocity(50, percent);
  shoot.setVelocity(50, percent);
  rightDrive.setVelocity(50, percent);
  leftDrive.setVelocity(50, percent);
  MotorRb.setVelocity(50, percent);
}

void buttons(){
  if (Controller1.ButtonR2.pressing()) { intake.setVelocity(100,rpm); } else { intake.setVelocity(0,rpm); }
  if (Controller1.ButtonL2.pressing()) { shoot.setVelocity(500,rpm); } else { shoot.setVelocity(0,rpm); }
  if (Controller1.ButtonR1.pressing()) { indexer.set(true); } else { indexer.set(false); }
  if (Controller1.ButtonL1.pressing()) { expansion.set(true); }
}

void autonomous(void) {
  return;
}

void usercontrol(void) {
  pre_userc();
  //while (true) {
  //  buttons();
  //  arcade_drive(Controller1.Axis4.position(), Controller1.Axis1.position());
  //  wait(20, msec);
  //}
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}

