#include "main.h"

void initializeGUI()
{
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
  pros::lcd::initialize();
  pros::delay(2000);
  chassis.sensorInit();
  pros::delay(300);
  pros::lcd::print(0, "%f, %f, %f, %f", chassis.frontRightDrive.get_position(), chassis.frontLeftDrive.get_position(), chassis.currentX, chassis.currentY);
  chassis.sensorInit();
  pros::delay(300);
  pros::lcd::print(0, "%f, %f, %f, %f", chassis.frontRightDrive.get_position(), chassis.frontLeftDrive.get_position(), chassis.currentX, chassis.currentY);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
  l.closeFile();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
