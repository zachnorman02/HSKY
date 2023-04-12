#pragma once

#include <memory>

#include "main.h"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/controller.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/misc.hpp"
#include "robot_constants.hpp"

namespace src::Chassis {

static Motor leftOne = Motor(CHASSIS_PORT_L1, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor leftTwo = Motor(CHASSIS_PORT_L2, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor leftThree = Motor(CHASSIS_PORT_L3, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor leftFour = Motor(CHASSIS_PORT_L4, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

static Motor rightOne = Motor(CHASSIS_PORT_R1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor rightTwo = Motor(CHASSIS_PORT_R2, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor rightThree = Motor(CHASSIS_PORT_R3, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
static Motor rightFour = Motor(CHASSIS_PORT_R4, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

// MotorGroup for the left side of the chassis
static MotorGroup leftChassisMotorGroup = {leftOne, leftTwo, leftThree, leftFour};

// MotorGroup for the right side of the chassis
static MotorGroup rightChassisMotorGroup = {rightOne, rightTwo, rightThree, rightFour};

// Chassis pointer for access to chassis model: chassis->getModel()
extern std::shared_ptr<ChassisController> chassis;
static Controller controller = Controller();

// Control loop functions
extern void initialize();
extern void act();

extern void setChassisBrakeMode(AbstractMotor::brakeMode mode);

} // namespace src::Chassis