#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
Chassis chassis(8, 7, 9, 11, 'G');
Intake intake(6, 17);
TrayTilter trayTilter(18);
Lift lift(1);

char *param;