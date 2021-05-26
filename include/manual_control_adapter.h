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
            double TopLeft = 0.0;
            double TopRight = 0.0;
            double BottomLeft = 0.0;
            double BottomRight = 0.0;

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

    // Snap the value fixed if it is too small
    double clip (double input, double prec)
    {
        if (inRange(-prec, prec, input))
            return prec;
        else
            return input;
    }

    // A normal cubic function, as an input-smoothing alternative
    #define cubic(x) x*x*x

    // Left Single Stick: Team's preferred adapter.
    // Both horizontal and vertical are from -1 to 1.
    /*
    MotorMetadata left_single_stick (double horizontal, double vertical)
    {
        // Smooth out inputs
        vertical = cubic(vertical);

        MotorMetadata result = MotorMetadata(); // Create metadata

        if (inRange(-EPS, EPS, horizontal)) // Straight
        {
            result.TopLeft = clip(vertical, EPS);
            result.TopRight = clip(vertical, EPS);
            result.BottomLeft = clip(vertical, EPS);
            result.BottomRight = clip(vertical, EPS);
        }
        else if (horizontal < 0.0) // Rotating Left
        {
            result.TopRight = clip(vertical, EPS);
            result.BottomRight = clip(vertical, EPS);

            result.TopLeft = clip(map(-1.0, 0.0, -vertical, 0.0, horizontal), EPS);
            result.BottomLeft = clip(map(-1.0, 0.0, -vertical, 0.0, horizontal), EPS);
        }
        else if (horizontal > 0.0) // Rotating Right
        {
            result.TopLeft = clip(vertical, EPS);
            result.BottomLeft = clip(vertical, EPS);

            result.TopRight = clip(map(0.0, 1.0, 0.0, vertical, horizontal), EPS);
            result.BottomRight = clip(map(0.0, 1.0, 0.0, vertical, horizontal), EPS);
        }
        else
        {
            result.TopLeft = 0.0;
            result.BottomLeft = 0.0;

            result.TopRight = 0.0;
            result.BottomRight = 0.0;
        }

        return result;
    }
    */
    MotorMetadata left_single_stick (double horizontal, double vertical)
    {
        // Smooth out inputs
        horizontal = cubic(horizontal);
        vertical = cubic(vertical);

        MotorMetadata result = MotorMetadata(); // Create metadata

        // Decide the turning mode (straight, left or right)
        if (horizontal < -EPS) // Driving left
        {
            result.TopRight = fabs(horizontal);
            result.BottomRight = fabs(horizontal);

            result.TopLeft = vertical;
            result.BottomLeft = vertical;
        }
        else if (horizontal > EPS) // Driving right
        {
            result.TopLeft = horizontal;
            result.BottomLeft = horizontal;

            result.TopRight = vertical;
            result.BottomRight = vertical;
        }
        else // Driving straight
        {
            result.TopLeft = vertical;
            result.BottomLeft = vertical;
            result.TopRight = vertical;
            result.BottomRight = vertical;
        }

        return result;
    }

    // Smoothed tank drive function
    MotorMetadata tank (double left, double right)
    {
        MotorMetadata result = MotorMetadata();
        if (fabs(left) < EPS)
        {
            result.TopLeft = 0;
            result.BottomLeft = 0;
        }
        else
        {
            result.TopLeft = left;
            result.BottomLeft = left;
        }

        if (fabs(right) < EPS)
        {
            result.TopRight = 0;
            result.BottomRight = 0;
        }
        else
        {
            result.TopRight = right;
            result.BottomRight = right;
        }

        return result;
    }

};
