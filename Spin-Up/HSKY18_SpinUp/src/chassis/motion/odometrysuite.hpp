#pragma once

#include "pros/rotation.hpp"

namespace src::Motion {

class OdometrySuite {
  public:
    // Constructor
    OdometrySuite(pros::Rotation *leftEncoder, pros::Rotation *rightEncoder, pros::Rotation *horizontalEncoder);

    // Control Functions
    void reset();
    void update();

    // Getters
    float getXPosition() { return this->xPosition; };
    float getYPosition() { return this->yPosition; };
    float getOrientation() { return this->orientation; };

  private:
    // Static Pointers to Encoders
    static pros::Rotation *leftEncoder;
    static pros::Rotation *rightEncoder;
    static pros::Rotation *horizontalEncoder;

    // Pose Variables
    float xPosition;
    float yPosition;
    float orientation;
    // Last Reset Variables
    float leftEncoderAtLastReset = 0;
    float rightEncoderAtLastReset = 0;
    float horizontalEncoderAtLastReset = 0;
    float orientationAtLastReset = 0;
    // Previous Cycle Variables
    float previousLeftEncoderValue;
    float previousRightEncoderValue;
    float previousHorizontalEncoderValue;
    float previousOrientation;
    float previousGlobalX;
    float previousGlobalY;

    // Math Functions
    void cartesian2Polar(float x, float y, float &r, float &theta);
    void polar2Cartesian(float r, float theta, float &x, float &y);
};
} // namespace src::Motion