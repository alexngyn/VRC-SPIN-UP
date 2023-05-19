#include "vex.h"
#include "vex_drivetrain.h"
#include "common.h"
#include "pos.cpp"
#include <cmath>
#include <math.h>

#pragma once

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

void shooot(int l) {
  if (!shoot.isSpinning()) {
    shoot.setVelocity(flywheelSpeed, rpm);
    shoot.spin(directionType::fwd);
    wait(3, sec);
  }
  for (int i=l; i > 0; i++) {
    indexer.set(true);
    wait(1, sec);
    indexer.set(false);
    wait(1, sec);
  }
  shoot.stop();
}