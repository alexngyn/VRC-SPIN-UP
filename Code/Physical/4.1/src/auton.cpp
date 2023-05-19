#include "common.h"
#include "auton.h"

static bool rollers = false, preload = false, colorRed = false;

static bool button_catch(int x_min, int x_max, int y_min, int y_max) {return (x_min < Brain.Screen.xPosition() && x_max > Brain.Screen.xPosition() && y_min < Brain.Screen.yPosition() && y_max > Brain.Screen.yPosition() && Brain.Screen.pressing()) ? true : false;}

static void input(void) {
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono40);
  Brain.Screen.setCursor(2,4);
  Brain.Screen.print("Roller");
  Brain.Screen.setCursor(2,15);
  Brain.Screen.print("Preload");
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

  Brain.Screen.setFillColor(white);
  Brain.Screen.setPenColor(black);
  Brain.Screen.drawRectangle(160, 150, 160, 60);
  Brain.Screen.setCursor(5,11);
  Brain.Screen.print("DONE");
  Brain.Screen.setFillColor(black);
  Brain.Screen.setPenColor(white);

  while (button_catch(160,320,150,210) != true) {
    if (button_catch(70,170,78,123)) {
      Brain.Screen.setFillColor((rollers) ? red : green);
      Brain.Screen.drawRectangle(70, 78, 100, 45);
      Brain.Screen.setCursor(3,6);
      Brain.Screen.print((rollers) ? "NO " : "YES");
      rollers = !rollers;
      waitUntil((Brain.Screen.pressing() != true)); 
    } 
    if (button_catch(305,405,78,123)) {
      Brain.Screen.setFillColor((preload) ? red : green);
      Brain.Screen.drawRectangle(305, 78, 100, 45);
      Brain.Screen.setCursor(3,18);
      Brain.Screen.print((preload) ? "NO " : "YES");
      preload = preload ? false : true;
      waitUntil((Brain.Screen.pressing() != true)); 
    } 
    wait(100, msec);
  }
  goalCoordinates = (colorRed) ? -1350 : 1350;
  indexer.set(false);
  clr_screen();
}

void pre_auton(void) {
  vexcodeInit();
  //input();
  wait(20, msec);
}

void auton(void) {
  //vex::task t1(pos);
  //clr_screen();
  //if (rollers) {
  //  //robotDrive.setDriveVelocity(30, percent);
  //  //robotDrive.driveFor(forward, 100, mm);
  //  //intake.setVelocity(200,rpm);
  //  //intake.rotateFor(reverse, 180, deg);
  //  //robotDrive.driveFor(reverse, 100, mm);
  //}
  //if (preload) {
  //  //robotDrive.turnFor(left, 12, degrees);
  //  //turn_to();
  //  shooot(2); 
  //}
}