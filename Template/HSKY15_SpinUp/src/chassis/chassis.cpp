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

void initialize() {
    setChassisBrakeMode(AbstractMotor::brakeMode::brake);
    resetImu();
}

void act() { // OpControl for chassis
    chassis->getModel()->arcade(
        controller.getAnalog(ControllerAnalog::leftY),
        controller.getAnalog(ControllerAnalog::rightX) * TURN_FACTOR);
}

} // namespace src::Chassis
