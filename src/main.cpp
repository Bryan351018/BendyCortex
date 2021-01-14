#include <v5.h>
#include <v5_vcs.h>
#include "autopilot.h"
#include "driver.h"

using namespace vex;

// Create competition object
competition RaceObj = competition();

int main()
{
    // Bind competition callback functions
    RaceObj.autonomous(bendy::autopilot);
    RaceObj.drivercontrol(bendy::driver);
}
