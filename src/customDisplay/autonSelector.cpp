#include "main.h"
#include "customDisplay/autonSelector.h"
#include <string>

int currentAutonMode = 0;
const int MAX_AUTON_MODE = 3;
const char autonNames[MAX_AUTON_MODE + 1][20] = {"Red Straight Cube", "Red Stacked Cube", "Blue Straight Cube", "Blue Stacked Cube"};
const char shortAutonNames[MAX_AUTON_MODE + 1][11] = {"R Straight", "R Stack", "B Straight", "B Stack"};
void initializeDisplay()
{
  pros::lcd::initialize();
}

void runAutonSelector()
{
  while (true)
  {
    if (pros::lcd::read_buttons() == LCD_BTN_LEFT)
    {
      currentAutonMode--;
      if (currentAutonMode < 0)
      {
        currentAutonMode = MAX_AUTON_MODE;
      }
    }
    else if (pros::lcd::read_buttons() == LCD_BTN_RIGHT)
    {
      currentAutonMode++;
      if (currentAutonMode > MAX_AUTON_MODE)
      {
        currentAutonMode = 1;
      }
    }
    else if (pros::lcd::read_buttons() == LCD_BTN_CENTER)
    {
      break;
    }

    pros::lcd::print(3, "Current Auton: %d", currentAutonMode);
    pros::lcd::print(4, autonNames[currentAutonMode]);

    pros::delay(20);
  }

  pros::lcd::print(5, autonNames[currentAutonMode]);
  master.print(2, 0, "%s", shortAutonNames);
}