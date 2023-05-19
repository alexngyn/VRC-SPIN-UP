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
// GPS                  gps           9               
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

void input(void) {
  bool r = false, p = false;
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
      Brain.Screen.setFillColor((p) ? red : green);
      Brain.Screen.drawRectangle(305, 78, 100, 45);
      Brain.Screen.setCursor(3,18);
      Brain.Screen.print((p) ? "NO " : "YES");
      waitUntil((Brain.Screen.pressing() != true)); 
      p = p ? false : true;
    }
    wait(100, msec);
  }
  clr_screen();
}

void pre_auton(void) {
  vexcodeInit();
  input();
}

void autonomous(void) {
  return;
}

void usercontrol(void) {
  
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}

