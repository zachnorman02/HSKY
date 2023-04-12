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


void initialize() {
    setChassisBrakeMode(AbstractMotor::brakeMode::brake);
}

void act() { // OpControl for chassis
    
    // chassis->getModel()->arcade(
    //     controller.getAnalog(ControllerAnalog::leftY),
    //     controller.getAnalog(ControllerAnalog::rightX) * TURN_FACTOR);

    Motor leftMotors [4] = {leftOne, leftTwo, leftThree, leftFour};
    Motor rightMotors [4] = {rightOne, rightTwo, rightThree, rightFour};

    float move = controller.getAnalog(ControllerAnalog::leftY);
    float turn = controller.getAnalog(ControllerAnalog::rightX) * TURN_FACTOR;

    for (int i = 0; i < 4; i++) {
        leftMotors[i].moveVoltage(12000 * (move + turn));
    }

    for (int i = 0; i < 4; i++) {
        rightMotors[i].moveVoltage(12000 * (move - turn));
    }
}

} // namespace src::Chassis
