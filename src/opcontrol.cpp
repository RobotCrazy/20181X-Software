#include "main.h"
#include <functional>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

const int MACROID_CUBE_DEPLOY = 1;

bool functionThing()
{
	return true;
}
void opcontrol()
{
	bool macroInitiated = false;
	bool macroID = 0;
	pros::controller_digital_e_t macroButton;
	//Syntax for setting a prereq function
	// Prereq p1;
	// p1.setPrereqFunction(functionThing);
	//chassisControl.remove();
	//pros::lcd::print(7, "%d", pros::Task::get_count());
	while (true)
	{
		if (macroInitiated)
		{
			if (macroID = MACROID_CUBE_DEPLOY && master.get_digital(macroButton))
			{
				trayTilter.deployCubesOP(macroButton);
				chassis.driveBackward(8, 2500, 12000, macroButton);

				//Code to deploy cube here
			}
		}
		else
		{
			chassis.driverControl();
			intake.driverControl();
			if (master.get_digital(DIGITAL_A))
			{
				macroInitiated = true;
			}
		}
		pros::delay(20);
	}
}