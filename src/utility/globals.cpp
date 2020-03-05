#include "main.h"

pros::Controller master(CONTROLLER_MASTER);
Chassis chassis(8, 7, 9, 11, 'G');
Intake intake(5, 17, 'H');
TrayTilter trayTilter(18, 'A');
Lift lift(1, 'B');

char *param;