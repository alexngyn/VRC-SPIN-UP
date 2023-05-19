#include "vex.h"
#include "vex_drivetrain.h"
#include "common.h"

static double previousLeftRotation, previousRightRotation, rightRotation, leftRotation, distanceLeft, distanceRight, distanceAverage;
//const static double drivebase = 158.437, driveKp = 0.5, driveKi = 0.2, driveKd = 0.2;
const static double drivebase = 158.437;
double xCoordinate, yCoordinate, Heading;
//static double driveError = 50, driveIntegral, driveDerivitive, drivePrevError, driveSpeed;
//static double turnError, turnIntegral, turnDerivitive, turnPrevError, turnSpeed;

/*
void drivepid(double desiredx, double desiredy) {
  
  double x1 = x, y1 = y;
  turn_to(x2,y2,d);
  double l = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
  robotDrive.driveFor(d, l, mm, wt);
  double x3 = GPS.xPosition(mm), y3 = GPS.yPosition(mm);
  if (fabs(x3-x2) > 50 | fabs(y3-y2) > 50) {go_to(x2,y2,d,wt);}
  

  while (fabs(driveError) > 30) {
    driveError = sqrt(pow(desiredx-xCoordinate,2) + pow(desiredy-yCoordinate,2));
    driveSpeed = driveError;

    leftDrive.spin(directionType::fwd, driveSpeed + turnSpeed, voltageUnits::volt);
    rightDrive.spin(directionType::fwd, driveSpeed - turnSpeed, voltageUnits::volt);
  }
}

void turnpid(double angl) {
  //robotDrive.turnToHeading(a, degrees, wt);
}

void turnpid(double desiredx, double desiredy) {
  
  double x1 = x, y1 = y, a = 0;
  if (y2-y1 == 0) { if (x2 > x1) {a = 90;} else if (x2 < x1) {a = -90;}} else { a = (atan((x2-x1)/(y2-y1))) * 180/M_PI; }
  if (y1 > y2) {a -= 180;}
  if (d == reverse) {a -= 180;}
  while (a) {}

  turnError = a - h;
  turnIntegral = turnIntegral + turnError;
  if (turnError == 0 | fabs(turnError) > 40) {turnIntegral = 0;}
  turnDerivitive = turnError - turnPrevError;
  turnPrevError = turnError;
  turnSpeed = Kp*turnError + Ki*turnIntegral + Kd*turnDerivitive;
  leftDrive.spin(forward, turnSpeed, voltageUnits::volt);
  
  double a = 0;

  turnpid(a);
}
*/

int pos() {
  while (true) {
    if (GPS.quality() > 0) {
      xCoordinate = GPS.xPosition(), yCoordinate = GPS.yPosition(), Heading = GPS.heading();
    } else {
      leftRotation = leftEncoder.position(rotationUnits::deg), rightRotation = rightEncoder.position(rotationUnits::deg);;
      distanceLeft = ((previousLeftRotation - leftRotation)/360)*319.19, distanceRight = ((previousRightRotation - rightRotation)/360)*319.19;
      previousLeftRotation = leftRotation, previousRightRotation = rightRotation;
      distanceAverage = (distanceLeft + distanceRight) / 2;
      xCoordinate += (cos(Heading) * distanceAverage);
      yCoordinate += (sin(Heading) * distanceAverage);
      Heading += ((distanceRight-distanceLeft)/(2*drivebase));
    }
    this_thread::sleep_for(50);
  }
  return 1;
}