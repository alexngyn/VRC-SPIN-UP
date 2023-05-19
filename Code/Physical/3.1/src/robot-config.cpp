#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor left1 = motor(PORT1, ratio18_1, false);
motor left2 = motor(PORT2, ratio18_1, true);
motor left3 = motor(PORT3, ratio18_1, false);
motor right1 = motor(PORT4, ratio18_1, true);
motor right2 = motor(PORT5, ratio18_1, false);
motor right3 = motor(PORT6, ratio18_1, true);
motor intake = motor(PORT7, ratio36_1, false);
motor shoot = motor(PORT8, ratio6_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}