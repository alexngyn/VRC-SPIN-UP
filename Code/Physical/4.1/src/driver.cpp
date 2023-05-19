#include "common.h"
#include "driver.h"

static int scurve(double speed) { return ((12 * pow(fabs(speed), EulerConstant)) / (pow(100, EulerConstant))) * (speed / fabs(speed)); }

static void arcade_drive(double x, double y) {
  leftDrive.spin(vex::directionType::fwd, scurve(Controller1.Axis2.value() + Controller1.Axis4.value()), voltageUnits::volt);
  rightDrive.spin(vex::directionType::fwd, scurve(Controller1.Axis2.value() - Controller1.Axis4.value()), voltageUnits::volt);
}

static void buttons(void) {
  if (Controller1.ButtonL2.pressing()) { intake.setVelocity(600,rpm); } else if (Controller1.ButtonL1.pressing()) { intake.setVelocity(-600,rpm); } else { intake.setVelocity(0,rpm); };
  if (Controller1.ButtonR2.pressing()) { shoot.setVelocity(flywheelSpeed,rpm); } else { shoot.setVelocity(0,rpm); }
  if (Controller1.ButtonR1.pressing()) { 
    indexer.set(true);
    wait(1, sec);
    indexer.set(false); 
    wait(1, sec);
    indexerCount += 1;
  }
  //if (Controller1.ButtonX.pressing()) { turn_to(goalCoordinates,goalCoordinates); }
  if (Controller1.ButtonA.pressing()) { expansion.set(true); }
  if (Controller1.ButtonB.pressing()) { indexerCount = 0; }
  //shoot.setVelocity(d/1000*120,rpm);
  Controller1.Screen.setCursor(2,4);
  Controller1.Screen.print(indexerCount);
  //if (indexerCount > 50) {Controller1.rumble(rumblePulse);}
  //if (Brain.timer(sec) > 50) {Controller1.rumble(rumbleLong);}
  if (Controller1.ButtonUp.pressing()) { flywheelSpeed += 50; } else if (Controller1.ButtonDown.pressing()) { flywheelSpeed -= 50; };
  Controller1.Screen.setCursor(2,10);
  Controller1.Screen.print(indexerCount);
  //Controller1.Screen.setCursor(1,4);
  //Controller1.Screen.print(xCoordinate);
  //Controller1.Screen.setCursor(1,10);
  //Controller1.Screen.print(xCoordinate);
  //Controller1.Screen.setCursor(1,16);
  //Controller1.Screen.print(Heading);
}

void usercontrol(void) {
  clr_screen();
  leftDrive.spin(directionType::fwd);
  rightDrive.spin(directionType::fwd);
  intake.spin(directionType::fwd);
  shoot.spin(directionType::fwd);
  Brain.resetTimer();
  //vex::thread::interruptAll();
  //vex::thread t1(pos);
  while (true) {
    buttons();
    arcade_drive(Controller1.Axis4.position(), Controller1.Axis2.position());
    wait(20, msec);
  }
}