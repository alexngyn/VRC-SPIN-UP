#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorLf = motor(PORT18, ratio18_1, true);
motor MotorLb = motor(PORT19, ratio18_1, false);
motor MotorRf = motor(PORT16, ratio18_1, false);
motor MotorRb = motor(PORT17, ratio18_1, true);
gps GPS = gps(PORT21, 0.00, -200.00, mm, 180);
controller Controller1 = controller(primary);
motor intake1 = motor(PORT8, ratio6_1, true);
motor intake2 = motor(PORT4, ratio6_1, false);
motor shoot1 = motor(PORT9, ratio6_1, true);
motor shoot2 = motor(PORT10, ratio6_1, true);
digital_out indexer = digital_out(Brain.ThreeWirePort.H);
digital_out expansion = digital_out(Brain.ThreeWirePort.G);
motor_group intake = motor_group( intake1, intake2 );
motor_group shoot = motor_group( shoot1, shoot2 );
motor_group leftDrive = motor_group( MotorLb, MotorLf );
motor_group rightDrive = motor_group( MotorRb, MotorRf );
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
  wait(50, msec);
}