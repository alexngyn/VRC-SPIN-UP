
//#include "common.h"

/*

static double previousLeftRotation, previousRightRotation, rightRotation, leftRotation, distanceLeft, distanceRight, distanceAverage;
//const static double drivebase = 158.437, driveKp = 0.5, driveKi = 0.2, driveKd = 0.2;
const static double turnKp = 0.5, turnKi = 0.2, turnKd = 0.2;
const static double drivebase = 158.437;
double xCoordinate, yCoordinate, Heading, Rotation;
double coordinate[2] = {xCoordinate,yCoordinate};
//static double driveError, driveIntegral, driveDerivitive, drivePrevError, driveSpeed;
static double turnError, turnIntegral, turnDerivitive, turnPrevError, turnSpeed;

static double sign (double number) {
  if (number > 0) {return 1;}
  if (number < 0) {return -1;}
  return 0;
}

static double find_min_angle (double targetHeading, double currentHeading) {
  double turnAngle = targetHeading - currentHeading;
  if (turnAngle > 180 || turnAngle < -180) {turnAngle = -1 * sign(turnAngle) * (360 - fabs(turnAngle));}
  return turnAngle;
}

*/
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

*/
/*

void turnToPID(double angl) {
  
}

void turnToPID(double desiredx, double desiredy) {
  const double currentx = xCoordinate, currenty = yCoordinate;
  double angl = 0;
  if (desiredx-currentx == 0) { if (desiredx > currentx) {angl = 90;} else if (desiredx < currentx) {angl = -90;}} else { angl = (atan((desiredx-currentx)/(desiredy-currenty))) * 180/M_PI; }
  if (currentx > desiredx) {angl -= 180;}
  turnToPID(angl);
}

void turnPID(double desiredAngleChange) {
  desiredAngleChange += Rotation;
  turnError = desiredAngleChange - Rotation;
  while(true){
    turnError = desiredAngleChange - Rotation;
    //if (turnError == 0 | fabs(turnError) > 45) {turnIntegral = 0;} else (turnIntegral += turnError;)
    //turnDerivitive = turnError - turnPrevError;
    //turnPrevError = turnError;
    //turnSpeed = Kp*turnError + Ki*turnIntegral + Kd*turnDerivitive;
    turnSpeed = turnKp*turnError;
    leftDrive.spin(forward, turnSpeed, voltageUnits::volt);
    if (turnError < 5) { wait(10, sec); break;}
  }
}

int pos() {
  while (true) {
    if (GPS.quality() > 10) {
      xCoordinate = GPS.xPosition(), yCoordinate = GPS.yPosition(), Heading = GPS.heading(), Rotation = GPS.rotation();
    } else {
      leftRotation = leftEncoder.position(rotationUnits::deg), rightRotation = rightEncoder.position(rotationUnits::deg);;
      distanceLeft = ((previousLeftRotation - leftRotation)/360)*319.19, distanceRight = ((previousRightRotation - rightRotation)/360)*319.19;
      previousLeftRotation = leftRotation, previousRightRotation = rightRotation;
      distanceAverage = (distanceLeft + distanceRight) / 2;
      xCoordinate += (cos(Heading) * distanceAverage);
      yCoordinate += (sin(Heading) * distanceAverage);
      Heading += ((distanceRight-distanceLeft)/(2*drivebase));
      Rotation += ((distanceRight-distanceLeft)/(2*drivebase));
    }
    this_thread::sleep_for(50);
  }
  return 1;
}
*/