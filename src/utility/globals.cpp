#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
Chassis chassis(1, 11, 2, 4, 'G');
Intake intake(6, 17);
TrayTilter trayTilter(5);
Lift lift(3);

char *param;