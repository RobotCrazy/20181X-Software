#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
Chassis chassis(1, 11, 2, 4, 'E');
Intake intake(16, 17);
TrayTilter trayTilter(5);
Lift lift(3);

char *param;