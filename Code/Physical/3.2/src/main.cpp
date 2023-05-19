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

bool button_catch(int x_min, int x_max, int y_min, int y_max) {return (x_min < Brain.Screen.xPosition() && x_max > Brain.Screen.xPosition() && y_min < Brain.Screen.yPosition() && y_max > Brain.Screen.yPosition() && Brain.Screen.pressing()) ? true : false;}

bool r = false, p = false, c = false;

void input(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono40);
  Brain.Screen.setCursor(2,4);
  Brain.Screen.print("Roller");
  Brain.Screen.setCursor(2,15);
  Brain.Screen.print("Preload");
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(70, 78, 100, 45);
  Brain.Screen.drawRectangle(305, 78, 100, 45);
  Brain.Screen.setCursor(3,6);
  Brain.Screen.print("NO");
  Brain.Screen.setCursor(3,18);
  Brain.Screen.print("NO");

  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(160, 150, 160, 60);
  Brain.Screen.setCursor(5,11);
  Brain.Screen.print("DONE");
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(white);

  while (button_catch(160,320,150,210) != true) {
    if (button_catch(70,170,78,123)) {
      Brain.Screen.setFillColor((r) ? red : green);
      Brain.Screen.drawRectangle(70, 78, 100, 45);
      Brain.Screen.setCursor(3,6);
      Brain.Screen.print((r) ? "NO " : "YES");
      r = r ? false : true;
      waitUntil((Brain.Screen.pressing() != true)); 
    } else if (button_catch(305,405,78,123)) {
      if (p) {
        if (c != true) {
          Brain.Screen.setCursor(3,17);
          Brain.Screen.print("BLUE");
          c = true;
        } else {
          Brain.Screen.setFillColor(red);
          Brain.Screen.drawRectangle(305, 78, 100, 45);
          Brain.Screen.setCursor(3,17);
          Brain.Screen.print(" NO ");
          p = false;
        }
      } else {
        Brain.Screen.setFillColor(green);
        Brain.Screen.drawRectangle(305, 78, 100, 45);
        Brain.Screen.setCursor(3,17);
        Brain.Screen.print("RED ");
        p = true;
      }
      waitUntil((Brain.Screen.pressing() != true)); 
    }
    wait(100, msec);
  }
  if (p) { indexer.set(true); }
  clr_screen();
}

void turn_to(double x2, double y2, directionType d=forward, bool wt=true) {
  double x1 = GPS.xPosition(mm), y1 = GPS.yPosition(mm), a;
  if (y2-y1 == 0) {
    if (x2 > x1) {a = 90;} else if (x2 < x1) {a = -90;} else {return;}
  } else {
    a = (atan((x2-x1)/(y2-y1))) * 180.0/3.141592653589793238463;
  }
  if (y1 > y2) {a -= 180;}
  if (d == reverse) {a -= 180;}
  robotDrive.turnToHeading(a, degrees, wt);
}

void go_to(double x2, double y2, directionType d=forward, bool wt=true) {
  // int r = 1350, b = -1350;
  double x1 = GPS.xPosition(mm), y1 = GPS.yPosition(mm);
  turn_to(x2,y2,d);
  double l = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
  robotDrive.driveFor(d, l, mm, wt);
  double x3 = GPS.xPosition(mm), y3 = GPS.yPosition(mm);
  if (fabs(x3-x2) > 50 | fabs(y3-y2) > 50) {go_to(x2,y2,d,wt);}
}

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
  input();
  intake.setVelocity(100,rpm);
  shoot.setVelocity(500,rpm);
}

void pre_userc(void) {
  clr_screen();
  intake.spin(forward);
  shoot.spin(forward);
}

void buttons(){
  if (Controller1.ButtonR2.pressing()) { intake.setVelocity(100,rpm); } else { intake.setVelocity(0,rpm); }
  if (Controller1.ButtonL2.pressing()) { shoot.setVelocity(500,rpm); } else { shoot.setVelocity(0,rpm); }
  if (Controller1.ButtonR1.pressing()) { indexer.set(true); } else { indexer.set(false); }
  if (Controller1.ButtonL1.pressing()) { expansion.set(true); }
}

void autonomous(void) {
  if (r) {
    robotDrive.driveFor(forward, 100, mm);
    intake.rotateFor(forward, 100, deg);
    robotDrive.driveFor(reverse, 100, mm);
  }
  if (p) {
    //robotDrive.turnFor(left, 12, degrees);
    double t = (c) ? -1350 : 1350;
    turn_to(t, t);
    shoot.spin(forward);
    wait(10, sec);
    shoot.stop();
  }
}

void usercontrol(void) {
  pre_userc();
  while (true) {
    buttons();
    robotDrive.arcade(Controller1.Axis4.position(), Controller1.Axis1.position());
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

