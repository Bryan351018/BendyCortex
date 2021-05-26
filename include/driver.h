#include <v5.h>
#include <v5_vcs.h>
#include "device_config.h"
#include "manual_control_adapter.h"

namespace bendy
{
    vex::controller Controller = vex::controller();

    // Raw axes input
    vex::controller::axis left_vertical = Controller.Axis3;
    vex::controller::axis right_vertical = Controller.Axis2;
    vex::controller::axis horizontal = Controller.Axis4;

    bool isTankDrive;

    /*
        About other preferred keybinds
        L1: grab ball
        L2: push ball
        R1: lift ball
        R2: eject ball
    */

    void base_update () // Update the base motor velocities
    {
        // VERY IMPORTANT: LOCATION OF THE DRIVING ADAPTER

        double h = horizontal.value() / 127.0;
        double lv = left_vertical.value() / 127.0;
        double rv = right_vertical.value() / 127.0;

        bendy::MotorMetadata data;

        // VERY IMPORTANT: CONDITIONAL DRIVING ADAPTERS
        if (isTankDrive)
            data = bendy::tank(lv, rv);
        else
            data = bendy::left_single_stick(h, lv);

        bendy::Wheel_TL.setVelocity(data.TopLeft * 100, vex::pct);
        bendy::Wheel_TR.setVelocity(data.TopRight * 100, vex::pct);
        bendy::Wheel_BL.setVelocity(data.BottomLeft * 100, vex::pct);
        bendy::Wheel_BR.setVelocity(data.BottomRight * 100, vex::pct);
    }

    void driver (bool tank) // The main function
    {
        isTankDrive = tank;

        left_vertical.changed(base_update);
        right_vertical.changed(base_update);
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
                bendy::Vortex_Left.setVelocity(100, vex::pct);
                bendy::Vortex_Right.setVelocity(100, vex::pct);
                bendy::Roller_Bottom.setVelocity(100, vex::pct);
            }
            else if (Controller.ButtonL2.pressing())
            {
                bendy::Vortex_Left.setVelocity(-100, vex::pct);
                bendy::Vortex_Right.setVelocity(-100, vex::pct);
                bendy::Roller_Bottom.setVelocity(-100, vex::pct);
            }
            else
            {
                bendy::Vortex_Left.setVelocity(0, vex::pct);
                bendy::Vortex_Right.setVelocity(0, vex::pct);
                bendy::Roller_Bottom.setVelocity(0, vex::pct);
            }

            if (Controller.ButtonR1.pressing())
            {
                bendy::Roller_Top.setVelocity(100, vex::pct);
                bendy::Roller_Bottom.setVelocity(100, vex::pct);
            }
            else if (Controller.ButtonR2.pressing())
            {
                bendy::Roller_Top.setVelocity(-100, vex::pct);
                bendy::Roller_Bottom.setVelocity(-100, vex::pct);
            }
            else
            {
                bendy::Roller_Top.setVelocity(0, vex::pct);
                // bendy::Roller_Bottom.setVelocity(0, vex::pct);
            }

            vex::task::sleep(20); // Good to have in infinite loops
        }
    }
};
