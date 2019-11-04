#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
Chassis chassis(1, 11, 2, 4, 'E');
Intake intake(5);
TrayTilter trayTilter(6);
Lift lift();
char *param;