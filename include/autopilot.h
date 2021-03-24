#include <v5.h>
#include <v5_vcs.h>
#include "device_config.h"

namespace bendy
{
    // The left and right motor groups for supporting 4-motor drivetrain
    vex::motor_group L_Group = vex::motor_group(bendy::Wheel_TL, bendy::Wheel_BL); // Left
    vex::motor_group R_Group = vex::motor_group(bendy::Wheel_TR, bendy::Wheel_BR); // Right



    // The circumference of a wheel, CONFIGURABLE
    const double wheelCircum = 320.0;

    // The width of the robot, about the length of the wheel axle, CONFIGURABLE
    const double trackWidth = 320.0;

    // The distance between the wheel axles, CONFIGURABLE
    const double wheelBase = 320.0;

    // The unit of distance measurement (mm / in / cm), CONFIGURABLE
    const vex::distanceUnits distUnit = mm;

    // The drivetrain pointer (to support deletion)
    vex::drivetrain *Bendy = new vex::drivetrain(L_Group, R_Group, wheelCircum, trackWidth, wheelBase, distUnit);

    // Controls the robot during the autonomous period.
    void autopilot()
    {
        // Set the drive and turn velocities, CONFIGURABLE
        // Units: pct / rpm / dps (percent / rotations per minute / degrees per second)
        // Velocities are doubles
        Bendy -> setDriveVelocity(1.0, pct);
        Bendy -> setTurnVelocity(1.0, pct);

        // Set the motor timeout, CONFIGURABLE
        // Units: sec / msec (seconds / miliseconds)
        // Time is a 32-bit integer
        Bendy -> setTimeout(3.0, sec);

        // Finally, set the brake mode, CONFIGURABLE
        // Supports coast / brake / hold
        Bendy -> setStopping(brake);



        // Here goes your automated steps!

        /*
        To drive forwards / backwards:
        Bendy -> driveFor(double distance, distanceUnits units)
        Where "units" can be: (mm / in / cm)
        Distance can be positive or negative
        */

        /*
        To turn:
        Bendy -> turnFor(double angle, rotationUnits units)
        Where "units" can be: (deg / rev / raw), meaning (degrees / revolutions / raw data)
        Angle can be positive or negative
        */


        // Free the Bendy pointer to allow manual control
        delete Bendy;
    }
};
