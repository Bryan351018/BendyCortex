#include <v5.h>
#include <v5_vcs.h>

using namespace vex;

namespace bendy
{
    // Motor objects
    // motor(PORT, Gear Unit Setting, Is Reversed)
    motor Wheel_TL      = motor(PORT1, ratio18_1, false);  // Top Left
    motor Wheel_TR      = motor(PORT14, ratio18_1, true);  // Top Right
    motor Wheel_BL      = motor(PORT2, ratio18_1, false);  // Bottom Left
    motor Wheel_BR      = motor(PORT3, ratio18_1, true);  // Bottom Right
    motor Vortex_Left   = motor(PORT11, ratio18_1, true);
    motor Vortex_Right  = motor(PORT17, ratio18_1, false);
    motor Roller_Bottom = motor(PORT7, ratio18_1, true);
    motor Roller_Top    = motor(PORT8, ratio18_1, false);
};
