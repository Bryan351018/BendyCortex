#include <v5.h>
#include <v5_vcs.h>
#include "device_config.h"

namespace bendy
{
    // The left and right motor groups for supporting 4-motor drivetrain
    vex::motor_group L_Group = vex::motor_group(bendy::Wheel_TL, bendy::Wheel_BL); // Left
    vex::motor_group R_Group = vex::motor_group(bendy::Wheel_TR, bendy::Wheel_BR); // Right

    // The Brain object, to get 3-Wire ports
    vex::brain Brain = vex::brain();

    // The circumference of a wheel, CONFIGURABLE
    const double wheelCircum = 12.566371;

    // The width of the robot, about the length of the wheel axle, CONFIGURABLE
    const double trackWidth = 14.75;

    // The distance between the wheel axles, CONFIGURABLE
    const double wheelBase = 12.0;

    // The unit of distance measurement (mm / in / cm), CONFIGURABLE
    const vex::distanceUnits distUnit = vex::distanceUnits::in;

    // Gyro object, to support gyro turning in the future
    vex::inertial Gyro = vex::inertial(PORT13);

    // The drivetrain pointer (to support deletion)
    // vex::drivetrain* Bendy = new vex::drivetrain(L_Group, R_Group, wheelCircum, trackWidth, wheelBase, distUnit);
    // Do this to support gyro turning
    vex::smartdrive* Bendy = new vex::smartdrive(L_Group, R_Group, Gyro, wheelCircum, trackWidth, wheelBase, vex::distanceUnits::in);

    // An enumeration holding 3 states of ball transformation, in, out, or not moving.
    enum triState
    {
        tri_in, tri_out, tri_off
    };

    // An enumeration holding 4 states of ball transformation, up, down, out or not moving.
    enum quadState
    {
        quad_up, quad_down, quad_out, quad_off
    };

    // An easy interface to set Bendy's grabbing mode (in / out / off)
    void setGrab (triState state)
    {
        if (state == tri_in)
        {
            Vortex_Left.setVelocity(100, vex::pct);
            Vortex_Right.setVelocity(100, vex::pct);
            Roller_Bottom.setVelocity(100, vex::pct);
        }
        else if (state == tri_out)
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
    }

    // An easy interface to set Bendy's lifting mode (up / down / off)
    void setLift (quadState state)
    {
        if (state == quad_up)
        {
            bendy::Roller_Top.setVelocity(100, vex::pct);
            bendy::Roller_Bottom.setVelocity(100, vex::pct);
        }
        else if (state == quad_down)
        {
            bendy::Roller_Top.setVelocity(-100, vex::pct);
            bendy::Roller_Bottom.setVelocity(-100, vex::pct);
        }
        else if (state == quad_out)
        {
            bendy::Roller_Top.setVelocity(100, vex::pct);
            bendy::Roller_Bottom.setVelocity(-100, vex::pct);
        }
        else
        {
            bendy::Roller_Top.setVelocity(0, vex::pct);
            bendy::Roller_Bottom.setVelocity(0, vex::pct);
        }
    }

    // Throws the ball.
    void throwBall ()
    {
        setLift(quad_up);
        vex::task::sleep(300);
        setLift(quad_off);

        setLift(quad_down);
        vex::task::sleep(150);
        setLift(quad_off);

        setLift(quad_up);
        vex::task::sleep(2500);
        setLift(quad_off);
    }

    // Ejects the ball.
    void ejectBall ()
    {
        setLift(quad_out);
        vex::task::sleep(1500);
        setLift(quad_off);
    }

    // Controls the robot during the autonomous period.
    void autopilot ()
    {
        // Set the drive and turn velocities, CONFIGURABLE
        // Units: pct / rpm / dps (percent / rotations per minute / degrees per second)
        // Velocities are doubles
        Bendy -> setDriveVelocity(30.0, pct);
        Bendy -> setTurnVelocity(30.0, pct);

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
        Bendy -> driveFor(142.0, distanceUnits::in);
        Bendy -> turnFor(90.0, rotationUnits::deg);
        setGrab(tri_in);
        Bendy -> driveFor(30.0, distanceUnits::in);
        setGrab(tri_off);
        throwBall();
        Bendy -> turnFor(-90.0, rotationUnits::deg);



        // Free the Bendy pointer to allow manual control
        delete Bendy;
    }
};
