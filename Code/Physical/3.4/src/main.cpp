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
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setCursor(2,6);
  Brain.Screen.print("76209M");
  Brain.Screen.setCursor(3,8);
  Brain.Screen.print("IMF");
  Brain.Screen.render();
};

bool button_catch(int x_min, int x_max, int y_min, int y_max) {return (x_min < Brain.Screen.xPosition() && x_max > Brain.Screen.xPosition() && y_min < Brain.Screen.yPosition() && y_max > Brain.Screen.yPosition() && Brain.Screen.pressing()) ? true : false;}

bool r = false, p = false, c = false, a;
int i = 0, t;

void input(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono40);
  Brain.Screen.setCursor(2,4);
  Brain.Screen.print("Roller");
  Brain.Screen.setCursor(2,15);
  Brain.Screen.print("Preload");
  Brain.Screen.setCursor(4,4);
  Brain.Screen.print("Intake");
  Brain.Screen.setCursor(4,15);
  Brain.Screen.print("Color");
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(70, 78, 100, 45);
  Brain.Screen.drawRectangle(305, 78, 100, 45);
  Brain.Screen.drawRectangle(70, 158, 100, 45);
  Brain.Screen.drawRectangle(305, 158, 100, 45);
  Brain.Screen.setCursor(3,6);
  Brain.Screen.print("NO");
  Brain.Screen.setCursor(3,18);
  Brain.Screen.print("NO");
  Brain.Screen.setCursor(5,16);
  Brain.Screen.print("NO");
  Brain.Screen.setCursor(5,17);
  Brain.Screen.print("RED ");

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
    } 
    if (button_catch(305,405,78,123)) {
      Brain.Screen.setFillColor((p) ? red : green);
      Brain.Screen.drawRectangle(305, 78, 100, 45);
      Brain.Screen.setCursor(3,18);
      Brain.Screen.print((r) ? "NO " : "YES");
      p = p ? false : true;
      waitUntil((Brain.Screen.pressing() != true)); 
    } 
    if (button_catch(305,405,78,123)) {
      Brain.Screen.setFillColor((p) ? red : green);
      Brain.Screen.drawRectangle(305, 78, 100, 45);
      Brain.Screen.setCursor(3,18);
      Brain.Screen.print((r) ? "NO " : "YES");
      p = p ? false : true;
      waitUntil((Brain.Screen.pressing() != true)); 
    } 
    if (button_catch(188,78,100,45)) {
      Brain.Screen.setFillColor((r) ? red : blue);
      Brain.Screen.drawRectangle(188, 78, 100, 45);
      Brain.Screen.setCursor(3,11);
      Brain.Screen.print((r) ? "RED " : "BLUE");
      c = c ? false : true;
      waitUntil((Brain.Screen.pressing() != true)); 
    } 
    wait(100, msec);
  }
  t = (c) ? -1350 : 1350;
  indexer.set(false);
  clr_screen();
}

void turn_to(double x2=t, double y2=t, directionType d=forward, bool wt=true) {
  double x1 = GPS.xPosition(mm), y1 = GPS.yPosition(mm), a;
  if (y2-y1 == 0) {
    if (x2 > x1) {a = 90;} else if (x2 < x1) {a = -90;} else {return;}
  } else {
    a = (atan((x2-x1)/(y2-y1))) * 180.0/3.141592653589793238463;
  }
  if (y1 > y2) {a -= 180;}
  if (d == reverse) {a -= 180;}
  //robotDrive.turnToHeading(a, degrees, wt);
}

void go_to(double x2, double y2, directionType d=forward, bool wt=true) {
  double x1 = GPS.xPosition(mm), y1 = GPS.yPosition(mm);
  turn_to(x2,y2,d);
  double l = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
  robotDrive.driveFor(d, l, mm, wt);
  double x3 = GPS.xPosition(mm), y3 = GPS.yPosition(mm);
  if (fabs(x3-x2) > 50 | fabs(y3-y2) > 50) {go_to(x2,y2,d,wt);}
}

void arcade_drive(double x, double y) {
  leftDrive.spin(vex::directionType::fwd, (Controller1.Axis2.value() + Controller1.Axis4.value()), vex::velocityUnits::pct);
  rightDrive.spin(vex::directionType::fwd, (Controller1.Axis2.value() - Controller1.Axis4.value()), vex::velocityUnits::pct);
}

void pre_auton(void) {
  vexcodeInit();
  input();
  wait(20, msec);
}

void shooot(int l) {
  if (!shoot.isSpinning()) {
    double d = sqrt(pow(t-GPS.yPosition(mm),2) + pow(t-GPS.yPosition(mm),2));
    shoot.setVelocity(d/1000*120,rpm);
    shoot.spin(forward);
    wait(3, sec);
  }
  for (i=l; i > 0; i++) {
    indexer.set(true);
    wait(1, sec);
    indexer.set(false);
    wait(1, sec);
  }
  shoot.stop();
}

void autonomous(void) {
  if (r) {
    robotDrive.setDriveVelocity(30, percent);
    robotDrive.driveFor(forward, 100, mm);
    intake.setVelocity(200,rpm);
    intake.rotateFor(forward, 180, deg);
    robotDrive.driveFor(reverse, 100, mm);
  }
  if (p) {
    robotDrive.turnFor(left, 12, degrees);
    //turn_to();
    shooot(2); 
  }
  if (a) {
    bool rs = false;
    int x = 1;
    if (GPS.yPosition(mm) > 0) { if (c) { rs = true; } } else if (GPS.yPosition(mm) < 0) { if (c) { x = -1; } else if (!c) { rs = true; x = -1;} }
    if (rs) {
      robotDrive.setDriveVelocity(100, percent);
      intake.spin(forward, 600, rpm);
      go_to(-300*x, 850*x);
      go_to(0, 600*x);
      go_to(400*x, 200*x);
      wait(1, sec);
      intake.stop();
      turn_to(t,t);
      shooot(3);
    } else {
      robotDrive.setDriveVelocity(100, percent);
      intake.spin(forward, 600, rpm);
      go_to(-900*x, 300*x);
      robotDrive.setDriveVelocity(50, percent);
      go_to(-600*x, 0);
      wait(1, sec);
      intake.stop();
      turn_to(t,t);
      shooot(3);
    }
  }
}

void buttons(void) {
  if (Controller1.ButtonL2.pressing()) { intake.setVelocity(600,rpm); } else if (Controller1.ButtonL1.pressing()) { intake.setVelocity(-600,rpm); } else { intake.setVelocity(0,rpm); };
  if (Controller1.ButtonR2.pressing()) { shoot.setVelocity(600,rpm); } else { shoot.setVelocity(0,rpm); }
  if (Controller1.ButtonR1.pressing()) { 
    indexer.set(true);
    wait(1, sec);
    indexer.set(false); 
    wait(1, sec);
    i += 1;
  }
  if (Controller1.ButtonX.pressing()) { turn_to(); }
  if (Controller1.ButtonA.pressing()) { expansion.set(true); }
  if (Controller1.ButtonB.pressing()) { i = 0; }
  double d = sqrt(pow(t-GPS.yPosition(mm),2) + pow(t-GPS.yPosition(mm),2));
  //shoot.setVelocity(d/1000*120,rpm);
  Controller1.Screen.setCursor(2,4);
  Controller1.Screen.print(i);
  if (i > 50) {Controller1.rumble(rumblePulse);}
  //if (Brain.timer(sec) > 50) {Controller1.rumble(rumbleLong);}
}

void usercontrol(void) {
  clr_screen();
  leftDrive.spin(directionType::fwd);
  rightDrive.spin(directionType::fwd);
  intake.spin(directionType::fwd);
  shoot.spin(directionType::fwd);
  Brain.resetTimer();
  while (true) {
    buttons();
    arcade_drive(Controller1.Axis4.position(), Controller1.Axis2.position());
    clr_screen();
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

