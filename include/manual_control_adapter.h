#include <math.h>

namespace bendy
{
    const double EPS = 0.1; // Epsilon, controller's precison

    /*
        A Motor Metadata class to hold multiple return values
        used later in adapter functions
    */
    struct MotorMetadata
    {
        public:
            double TopLeft = 0;
            double TopRight = 0;
            double BottomLeft = 0;
            double BottomRight = 0;

            MotorMetadata(){}

    };

    // A function used to check if a value is in a certain range.
    bool inRange(double left, double right, double current)
    {
        if (current >= left && current <= right)
            return true;
        else
            return false;
    }

    // A mapping function used in case of turning
    double map (double p_min, double p_max, double c_min, double c_max,
        double current)
    {
        // (current - p_min): remove offset
        // * ((c_max - c_min) / (p_max - p_min)): calculate map ratio
        // + c_min: reapply offset
        return (current - p_min) * ((c_max - c_min) / (p_max - p_min)) + c_min;
    }

    // A normal cubic function, as an input-smoothing alternative
    #define cubic(x) x*x*x

    // Left Single Stick: Team's preferred adapter.
    // Both horizontal and vertical are from -1 to 1.
    MotorMetadata left_single_stick (double horizontal, double vertical)
    {
        // Smooth out inputs
        vertical = cubic(vertical);

        MotorMetadata result = MotorMetadata(); // Create metadata

        if (inRange(-EPS, EPS, horizontal)) // Straight
        {
            result.TopLeft = vertical;
            result.TopRight = vertical;
            result.BottomLeft = vertical;
            result.BottomRight = vertical;
        }
        else if (horizontal < 0.0) // Rotating Left
        {
            result.TopRight = vertical;
            result.BottomRight = vertical;

            result.TopLeft = map(-1.0, 0.0, -vertical, 0.0, horizontal);
            result.BottomLeft = map(-1.0, 0.0, -vertical, 0.0, horizontal);
        }
        else if (horizontal > 0.0) // Rotating Right
        {
            result.TopLeft = vertical;
            result.BottomLeft = vertical;

            result.TopRight = map(0.0, 1.0, 0.0, vertical, horizontal);
            result.BottomRight = map(0.0, 1.0, 0.0, vertical, horizontal);
        }
        else{}

        return result;
    }
};
