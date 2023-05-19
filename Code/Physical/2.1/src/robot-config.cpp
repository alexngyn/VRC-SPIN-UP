#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Motor7 = motor(PORT1, ratio18_1, false);
motor mgrMotorA = motor(PORT6, ratio18_1, true);
motor mgrMotorB = motor(PORT20, ratio18_1, false);
motor_group mgr = motor_group(mgrMotorA, mgrMotorB);
motor mglMotorA = motor(PORT19, ratio18_1, false);
motor mglMotorB = motor(PORT5, ratio18_1, true);
motor_group mgl = motor_group(mglMotorA, mglMotorB);

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