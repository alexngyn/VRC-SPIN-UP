using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorLf;
extern motor MotorLm;
extern motor MotorLb;
extern motor MotorRf;
extern motor MotorRm;
extern motor MotorRb;
extern gps GPS;
extern controller Controller1;
extern motor intake;
extern motor shoot;
extern digital_out indexer;
extern digital_out expansion;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern drivetrain robotDrive;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );