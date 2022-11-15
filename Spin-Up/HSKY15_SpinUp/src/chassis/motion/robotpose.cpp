#include "robotpose.hpp"

/**
 * @brief Construct a new Robot Pose object that represents the current position
 * and orientation of the robot with x position, y position, and angle.
 */
RobotPose::RobotPose() {
    this->xPosition = 0;
    this->yPosition = 0;
    this->theta = 0;
}

/**
 * @brief Construct a new Robot Pose object with the given position and orientation
 *
 * @param x absolute x position of the robot [in]
 * @param y absolute y position of the robot [in]
 * @param theta absolute orientation of the robot [rad]
 */
RobotPose::RobotPose(float x, float y, float theta) {
    this->xPosition = x;
    this->yPosition = y;
    this->theta = theta;
}

/**
 * @brief Destroy the Robot Pose object
 */
RobotPose::~RobotPose() {}

/**
 * @brief Gets the current x-position of the robot.
 *
 * @return the current x-position of the robot as a float [in]
 */
float RobotPose::getXPosition() { return this->xPosition; }

/**
 * @brief Gets the current y-position of the robot.
 *
 * @return the current y-position of the robot as a float [in]
 */
float RobotPose::getYPosition() { return this->yPosition; }

/**
 * @brief Gets the current angle of the robot.
 *
 * @return the current angle of the robot as a float [rad]
 */
float RobotPose::getTheta() { return this->theta; }

/**
 * @brief Determines if this RobotPose is equal to the given RobotPose.
 *
 * @param other the RobotPose to compare to
 */
bool RobotPose::operator==(const RobotPose &other) const {
    return this->xPosition == other.xPosition && this->yPosition == other.yPosition && this->theta == other.theta;
}

/**
 * @brief Determines if this RobotPose is not equal to the given RobotPose.
 *
 * @param other the RobotPose to compare to
 */
bool RobotPose::operator!=(const RobotPose &other) const { return !(*this == other); }