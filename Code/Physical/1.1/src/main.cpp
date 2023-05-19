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
// Motor1               motor         1               
// Motor2               motor         2               
// Motor3               motor         3               
// Motor4               motor         4               
// Motor5               motor         5               
// Motor6               motor         6               
// Motor7               motor         7               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_drivetrain.h"
#include <cmath>

using namespace vex;

competition Competition;

void pre_auton(void) {
  vexcodeInit();
  Motor1.spin(forward);
  Motor2.spin(forward);
  Motor3.spin(forward);
  Motor4.spin(forward);
  Motor5.spin(forward);
  Motor6.spin(forward);
  Motor7.setVelocity(200,rpm);
}

void motorvec(double ls, double rs){
  Motor1.setVelocity(ls,percent);
  Motor2.setVelocity(ls,percent);
  Motor3.setVelocity(ls,percent);
  Motor4.setVelocity(rs,percent);
  Motor5.setVelocity(rs,percent);
  Motor6.setVelocity(rs,percent);
}

void move() {
  double vs = Controller1.Axis2.position();
  double hs = Controller1.Axis4.position();
  double ls = (hs < 0) ? vs - fabs(hs) : vs;
  double rs = (hs > 0) ? vs - fabs(hs) : vs;
  motorvec(ls,rs);
}

void roller() {
  if (Controller1.ButtonR2.pressing()) { Motor7.spinFor(forward, 180, degrees); }
  if (Controller1.ButtonL2.pressing()) { Motor7.spinFor(reverse, 180, degrees); }
}

void display() {
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.clearLine();
  Controller1.Screen.print("hi");
  Controller1.Screen.newLine();
  Controller1.Screen.clearLine();
  Controller1.Screen.print("hi");
  Controller1.Screen.newLine();
  Controller1.Screen.clearLine();
  Controller1.Screen.print("hi");
}

void autonomous(void) {
  return;
}

void usercontrol(void) {
  while (true) {
    move();
    roller();
    display();
    wait(20, msec);
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

