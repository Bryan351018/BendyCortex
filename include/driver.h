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

    void motor_update () // Update the motor velocities
    {
        double v = vertical.value() / 127;
        double h = horizontal.value() / 127;

        bendy::MotorMetadata data;
        data = bendy::left_single_stick(v, h);

        bendy::Wheel_TL.setVelocity(data.TopLeft * 100, vex::pct);
        bendy::Wheel_TR.setVelocity(data.TopRight * 100, vex::pct);
        bendy::Wheel_BL.setVelocity(data.BottomLeft * 100, vex::pct);
        bendy::Wheel_BR.setVelocity(data.BottomRight * 100, vex::pct);
    }

    void driver () // The main function
    {
        vertical.changed(motor_update);
        horizontal.changed(motor_update);

        bendy::Wheel_TL.spin(vex::fwd);
        bendy::Wheel_TR.spin(vex::fwd);
        bendy::Wheel_BL.spin(vex::fwd);
        bendy::Wheel_BR.spin(vex::fwd);

        while (true) // Infinite loop
        {


            vex::task::sleep(20); // Good to have in infinite loops
        }
    }
};
