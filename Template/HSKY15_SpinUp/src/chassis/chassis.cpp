#include "chassis.hpp"

#include "main.h"
#include "okapi/impl/control/iterative/iterativeControllerFactory.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "pros/misc.h"
#include <cmath>

namespace src::Chassis {

// Initalize chassis pointer using motor group and dimensions
std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors(leftChassisMotorGroup, rightChassisMotorGroup)
        .withSensors(leftChassisMotorGroup.getEncoder(), rightChassisMotorGroup.getEncoder())
        .withDimensions(AbstractMotor::gearset::blue, {{WHEEL_DIAMETER, WHEEL_TRACK}, imev5BlueTPR})
        .build();

// Field Constants Class
static Motion::FieldConstants fieldConstants = Motion::FieldConstants();

// Static OdometrySuite instance
static Motion::OdometrySuite odometrySuite = Motion::OdometrySuite(leftEncoder, rightEncoder, horizontalEncoder);

void setChassisBrakeMode(AbstractMotor::brakeMode mode) {
    chassis->getModel()->setBrakeMode(mode);
}

void resetImu(bool print = true) {
    imuSensor.reset();
    int time = pros::millis();
    int iter = 0;
    while (imuSensor.is_calibrating()) {
        if (print) {
            printf("IMU Calibrating... %d [ms]\n", iter);
        }
        iter += 100;
        if (iter >= 2500) { // IMU should not take more than 2500 ms to calibrate
            if (print) {
                printf("IMU Calibration Failed!\n");
            }
            break;
        }
        pros::delay(100);
    }
    if (print) {
        printf("IMU Calibrated in %d [ms]\n", iter - time);
    }
}

/**
 * @brief Set the Robot's Starting Position as one of the predefined positions on the field
 *
 * @param startPosition an enum representing which position has been selected (based on the autonomous selection)
 */
void setRobotStartingPosition(Motion::StartingPosition startPosition) {
    fieldConstants.setStartingPosition(startPosition);
}

void initialize() {
    setChassisBrakeMode(AbstractMotor::brakeMode::brake);
    resetImu();
    odometrySuite.initialize();
}

void update() {
    // Nifty function that runs in control loop. Useful for debugging during opcontrol
    // printf("IMU: %f", imuSensor.get_heading());
    // printf("Ultrasonic: %d", ultrasonic.get_value());
    // printf("Left Encoder: %d", chassis->getModel()->getSensorVals()[0]);
    // printf("Right Encoder: %d", chassis->getModel()->getSensorVals()[1]);
    odometrySuite.update();
}

void act() { // OpControl for chassis
    chassis->getModel()->arcade(
        controller.getAnalog(ControllerAnalog::leftY),
        controller.getAnalog(ControllerAnalog::rightX) * TURN_FACTOR);
}

} // namespace src::Chassis
