namespace bendy
{
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

    // Left Single Stick: Team's preferred adapter.
    // Both horizontal and vertical are from -1 to 1.
    MotorMetadata left_single_stick (double horizontal, double vertical)
    {
        MotorMetadata result = MotorMetadata(); // Create metadata

        if (horizontal == 0) // Straight
        {
            result.TopLeft = vertical;
            result.TopRight = vertical;
            result.BottomLeft = vertical;
            result.BottomRight = vertical;
        }
        else if (horizontal < 0) // Rotating Left
        {
            result.TopRight = vertical;
            result.BottomRight = vertical;

            result.TopLeft = (horizontal - -0.5) * 2;
            result.BottomLeft = (horizontal - -0.5) * 2;
        }
        else // Rotating Right
        {
            result.TopLeft = vertical;
            result.BottomLeft = vertical;

            result.TopRight = (horizontal - 0.5) * 2;
            result.BottomRight = (horizontal - 0.5) * 2;
        }

        return result;
    }
};
