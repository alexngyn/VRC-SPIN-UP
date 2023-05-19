#include "common.h"

int EulerConstant = std::exp(1.0);

int flywheelSpeed = 350;
int goalCoordinates = 1350;
int indexerCount = 0;

void waitUntil(bool condition) {while (!(condition)) {wait(10, msec);};}

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