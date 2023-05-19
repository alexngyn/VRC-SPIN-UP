#ifndef COMMON_H_
#define COMMON_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <list>
#include "v5.h"
#include "v5_vcs.h"
#include "robot-config.h"

extern int EulerConstant;
extern int flywheelSpeed;
extern int goalCoordinates;
extern int indexerCount;

void waitUntil(bool condition);

void clr_screen(void);

void shooot(int l);

#endif