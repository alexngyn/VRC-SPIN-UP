using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorLf;
extern motor MotorLb;
extern motor MotorRf;
extern motor MotorRb;
extern gps GPS;
extern controller Controller1;
extern motor intake1;
extern motor intake2;
extern motor shoot1;
extern motor shoot2;
extern digital_out indexer;
extern digital_out expansion;
extern motor_group shoot;
extern motor_group intake;
extern motor_group leftDrive;
extern motor_group rightDrive;
// extern smartdrive robotDrive;
extern encoder leftEncoder;
extern encoder rightEncoder;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );