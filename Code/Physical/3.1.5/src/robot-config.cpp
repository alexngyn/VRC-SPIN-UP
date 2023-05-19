#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorLf = motor(PORT1, ratio18_1, true);
motor MotorLm = motor(PORT2, ratio18_1, false);
motor MotorLb = motor(PORT3, ratio18_1, true);
motor MotorRf = motor(PORT4, ratio18_1, false);
motor MotorRm = motor(PORT5, ratio18_1, true);
motor MotorRb = motor(PORT6, ratio18_1, false);
gps GPS = gps(PORT7, 0.00, 180.00, mm, 180);
controller Controller1 = controller(primary);
motor intake = motor(PORT8, ratio18_1, false);
motor shoot = motor(PORT9, ratio6_1, false);
digital_out indexer = digital_out(Brain.ThreeWirePort.A);
digital_out expansion = digital_out(Brain.ThreeWirePort.B);
motor_group leftDrive = motor_group( MotorLb, MotorLm, MotorLf );
motor_group rightDrive = motor_group( MotorRb, MotorRm, MotorLf );
// smartdrive motor_group &l, motor_group &r, vex::guido(&g, double wheelTravel=320, double trackWidth=320, double wheelBase=130, distanceUnits unit=distanceUnits::mm, double externalGearRatio=1.0)
smartdrive robotDrive = smartdrive( leftDrive, rightDrive, GPS, 319.19, 316.87, 40); 

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