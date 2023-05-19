#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorLf = motor(PORT18, ratio18_1, true);
motor MotorLm = motor(PORT19, ratio18_1, false);
motor MotorLb = motor(PORT20, ratio18_1, true);
motor MotorRf = motor(PORT16, ratio18_1, false);
motor MotorRm = motor(PORT17, ratio18_1, true);
motor MotorRb = motor(PORT15, ratio18_1, false);
gps GPS = gps(PORT7, 0.00, -200.00, mm, 180);
controller Controller1 = controller(primary);
motor intake = motor(PORT10, ratio18_1, false);
motor shoot = motor(PORT9, ratio6_1, false);
digital_out indexer = digital_out(Brain.ThreeWirePort.H);
digital_out expansion = digital_out(Brain.ThreeWirePort.G);
motor_group leftDrive = motor_group( MotorLb, MotorLm, MotorLf );
motor_group rightDrive = motor_group( MotorRb, MotorRm, MotorRf );
// smartdrive motor_group &l, motor_group &r, vex::guido(&g, double wheelTravel=320, double trackWidth=320, double wheelBase=130, distanceUnits unit=distanceUnits::mm, double externalGearRatio=1.0)
// smartdrive robotDrive = smartdrive( leftDrive, rightDrive, GPS, 319.19, 316.87, 40 ); 
// drivetrain(motor_group &l, motor_group &r, double wheelTravel=320, double trackWidth=320, double wheelBase=130, distanceUnits unit=distanceUnits::mm, double externalGearRatio=1.0)
drivetrain robotDrive = drivetrain( leftDrive, rightDrive, 319.19, 316.87, 40 );

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain GPS
  wait(200, msec);
  GPS.calibrate();
  Brain.Screen.print("Calibrating GPS for Drivetrain");
  // wait for the GPS calibration process to finish
  while (GPS.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}