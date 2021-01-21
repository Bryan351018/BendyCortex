#include <v5.h>
#include <v5_vcs.h>
#include "device_config.h"
#include "manual_control_adapter.h"


namespace bendy // Custom namespace
{
    // The controller object
    vex::controller Controller = vex::controller();

    // Raw axes input
    vex::controller::axis vertical = Controller.Axis3;
    vex::controller::axis horizontal = Controller.Axis4;



    void driver () // The main function
    {
        while (true) // Infinite loop
        {


            vex::task::sleep(20); // Good to have in infinite loops
        }
    }
}
