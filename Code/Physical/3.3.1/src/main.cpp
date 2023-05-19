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

void autonomous(void) {
  return;
}



void usercontrol(void) {
  rightDrive.spin(forward);
  leftDrive.spin(forward);
  //MotorRb.spin(forward);
  rightDrive.setVelocity(50, percent);
  leftDrive.setVelocity(50, percent);
  //MotorRb.setVelocity(50, percent);
  //while (true) {
  //  buttons();
  //  arcade_drive(Controller1.Axis4.position(), Controller1.Axis1.position());
  //  wait(20, msec);
  //}
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  while (true) {
    wait(100, msec);
  }
}

