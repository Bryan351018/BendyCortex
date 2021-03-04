#include <v5.h>
#include <v5_vcs.h>
#include "device_config.h"
#include "manual_control_adapter.h"

namespace bendy
{
    vex::controller Controller = vex::controller();

    // Raw axes input
    vex::controller::axis vertical = Controller.Axis3;
    vex::controller::axis horizontal = Controller.Axis4;

    /*
        About other preferred keybinds
        L1: grab ball
        L2: push ball
        R1: lift ball
        R2: eject ball
    */

    void base_update () // Update the base motor velocities
    {
        double h = horizontal.value() / 127.0;
        double v = vertical.value() / 127.0;

        bendy::MotorMetadata data;
        data = bendy::left_single_stick(h, v);

        bendy::Wheel_TL.setVelocity(data.TopLeft * 100, vex::pct);
        bendy::Wheel_TR.setVelocity(data.TopRight * 100, vex::pct);
        bendy::Wheel_BL.setVelocity(data.BottomLeft * 100, vex::pct);
        bendy::Wheel_BR.setVelocity(data.BottomRight * 100, vex::pct);
    }

    void driver () // The main function
    {
        vertical.changed(base_update);
        horizontal.changed(base_update);

        bendy::Wheel_TL.spin(vex::fwd);
        bendy::Wheel_TR.spin(vex::fwd);
        bendy::Wheel_BL.spin(vex::fwd);
        bendy::Wheel_BR.spin(vex::fwd);
        bendy::Vortex_Left.spin(vex::fwd);
        bendy::Vortex_Right.spin(vex::fwd);
        bendy::Roller_Top.spin(vex::fwd);
        bendy::Roller_Bottom.spin(vex::fwd);

        while (true) // Infinite loop
        {
            // Update motors that are not part of the base
            if (Controller.ButtonL1.pressing())
            {

            }
            if (Controller.ButtonL2.pressing())
            {

            }
            if (Controller.ButtonR1.pressing())
            {

            }
            if (Controller.ButtonR2.pressing())
            {

            }

            vex::task::sleep(20); // Good to have in infinite loops
        }
    }
};
