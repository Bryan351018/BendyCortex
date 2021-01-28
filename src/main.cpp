#include <v5.h>
#include <v5_vcs.h>

#ifndef AUTOPILOT_H
#include "autopilot.h"
#endif

#ifndef DRIVER_H
#include "driver.h"
#endif

using namespace vex;

// Create competition object
competition RaceObj = competition();

int main ()
{
    // Rumble controller, to notify the driver
    controller().rumble("..");

    // Bind competition callback functions
    RaceObj.autonomous(autopilot);
    RaceObj.drivercontrol(driver);
}
