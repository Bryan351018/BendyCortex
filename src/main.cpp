#include <v5.h>
#include <v5_vcs.h>
#include "autopilot.h"
#include "driver.h"


using namespace vex;

// Create competition object
competition RaceObj = competition();

// Create controller object
vex::controller Controller = vex::controller();

int main ()
{
    // Rumble controller, to notify the driver
    Controller.rumble("..");
    Controller.Screen.print("Press X or Y");
    Controller.Screen.newLine();
    Controller.Screen.print("X: auto, Y: manual");

    while (true)
    {
        // Autonomous
        if (Controller.ButtonX.pressing())
        {
            Controller.Screen.clearScreen();
            bendy::autopilot();
            break;
        }

        // Manual
        if (Controller.ButtonY.pressing())
        {
            Controller.Screen.clearScreen();
            Controller.rumble("--");
            Controller.Screen.print("Press X or Y");
            Controller.Screen.newLine();
            Controller.Screen.print("X: leftStick, Y: tank");

            // Choose adapter mode
            while (true)
            {
                // Left single stick
                if (Controller.ButtonX.pressing())
                {
                    Controller.Screen.clearScreen();
                    bendy::driver(false);
                    break;
                }

                // Tank drive
                if (Controller.ButtonY.pressing())
                {
                    Controller.Screen.clearScreen();
                    bendy::driver(true);
                    break;
                }
                vex::task::sleep(20);
            }
        }

        vex::task::sleep(20);
    }

    // // Bind competition callback functions
    // //RaceObj.autonomous(bendy::simpleAutopilot);
    // Controller.ButtonX.pressed(bendy::autopilot);
    //
    //
    // //controller().rumble(". -");
    // //RaceObj.drivercontrol(bendy::driver);
    // Controller.ButtonY.pressed(bendy::driver);

}
