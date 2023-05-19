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
// Controller1          controller                    
// left1                motor         1               
// left2                motor         2               
// left3                motor         3               
// right1               motor         4               
// right2               motor         5               
// right3               motor         6               
// intake               motor         7               
// shoot                motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_drivetrain.h"
#include <cmath>

using namespace vex;

competition Competition;

void pre_auton(void) {
  vexcodeInit();
  intake.setVelocity(100,rpm);
  shoot.setVelocity(500,rpm);
}

void pre_userc(void) {
  left1.spin(forward);
  left2.spin(forward);
  left3.spin(forward);
  right1.spin(forward);
  right2.spin(forward);
  right3.spin(forward);
  intake.spin(forward);
  shoot.spin(forward);
}

void motorvec(double ls, double rs){
  left1.setVelocity(ls,percent);
  left2.setVelocity(ls,percent);
  left3.setVelocity(ls,percent);
  right1.setVelocity(rs,percent);
  right2.setVelocity(rs,percent);
  right3.setVelocity(rs,percent);
}

void move() {
  double vs = Controller1.Axis2.position(), hs = Controller1.Axis4.position() * 0.9, ls, rs;
  if (hs < 0) {ls = vs, rs = vs + fabs(hs);} else if (hs > 0) {rs = vs, ls = vs + fabs(hs);} else {ls = vs, rs = vs;}
  if (ls > 100) {rs -= (ls - 100),ls -= (ls - 100);} else if (rs > 100) {ls -= (rs - 100),rs -= (rs - 100);};
  motorvec(ls,rs);
}

void intak(){
  if (Controller1.ButtonR2.pressing() | (Controller1.ButtonL2.pressing()) ) { intake.setVelocity(100,rpm); } else { intake.setVelocity(0,rpm); }
  if (Controller1.ButtonR1.pressing() | (Controller1.ButtonL1.pressing()) ) { shoot.setVelocity(500,rpm); } else { shoot.setVelocity(0,rpm); }
}

void display() {
  Controller1.Screen.setCursor(1,3);
  Controller1.Screen.print("76209M-IMF");
}

void autonomous(void) {
  return;
}

void usercontrol(void) {
  pre_userc();
  while (true) {
    move();
    intak();
    display();
    wait(5, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}

