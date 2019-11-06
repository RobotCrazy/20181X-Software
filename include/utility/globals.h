#include "api.h"
#include "subsystems/chassis.hpp"
#include "subsystems/trayTilter.hpp"
#include "utility/mathUtil.h"

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

extern pros::Controller master;
extern Chassis chassis;
extern Intake intake;
extern TrayTilter trayTilter;
extern Lift lift;
extern char *param;

#endif