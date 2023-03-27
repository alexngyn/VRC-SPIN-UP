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
// Motor7               motor         1               
// mgr                  motor_group   6, 20           
// mgl                  motor_group   19, 5           
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vex_drivetrain.h"
#include <cmath>

using namespace vex;

competition Competition;

void pre_auton(void) {
  vexcodeInit();
  mgr.setVelocity(100,percent);
  mgl.setVelocity(100,percent);
  Motor7.setVelocity(200,rpm);
}

void pre_userc(void) {
  mgr.spin(forward);
  mgl.spin(forward);
}

void move() {
  double vs = Controller1.Axis2.position(), hs = Controller1.Axis4.position() * 0.9, ls, rs;
  if (hs < 0) {ls = vs, rs = vs + fabs(hs);} else if (hs > 0) {rs = vs, ls = vs + fabs(hs);} else {ls = vs, rs = vs;}
  if (ls > 100) {rs -= (ls - 100),ls -= (ls - 100);} else if (rs > 100) {ls -= (rs - 100),rs -= (rs - 100);};
  mgr.setVelocity(ls,percent);
  mgl.setVelocity(rs,percent);
}

void roller() {
  if (Controller1.ButtonR2.pressing()) { Motor7.spinFor(forward, 180, degrees); }
  if (Controller1.ButtonL2.pressing()) { Motor7.spinFor(reverse, 180, degrees); }
}

void move(double left, double right) {
  mgl.spinFor(forward, left/319.186, turns, false);
  mgr.spinFor(forward, right/319.186, turns, false);
}

void autonomous(void) {
  //wait(50, sec);
  move(200,200);
  while (true) {
    wait(5, msec);
  }
}

void usercontrol(void) {
  pre_userc();
  while (true) {
    move();
    roller();
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

