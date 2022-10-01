#include "main.h"
#include "api.h"
#include "chassis/chassis.hpp"
#include "okapi/api.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "scorer/scorer.hpp"

// Define included namespaces and types
#define Chassis src::Chassis
#define Scorer src::Scorer
#define Pose Chassis::Pose_t

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
    static bool pressed = false;
    pressed = !pressed;
    if (pressed) {
        pros::lcd::set_text(2, "I was pressed!");
    } else {
        pros::lcd::clear_line(2);
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    pros::lcd::set_text(1, "Hello PROS User!");

    pros::lcd::register_btn1_cb(on_center_button);

    // Updates RobotPose every 10 ms
    pros::Task odometryHandle(Chassis::odometryTask);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    Pose currentPose = Chassis::getRobotPose();             // Initial Pose is [0, 0, 0]
    Scorer::setIntakeMotion(Scorer::IntakeState::INTAKING); // Start intaking
    Chassis::movePID(24, 24, 1000);                         // move forward 24 inches
    Chassis::gyroPID(90, true);                             // turn 90 degrees clockwise
    Scorer::pullDownAndFireCatapult();                      // pull down and fire catapult
    Scorer::setIntakeMotion(Scorer::IntakeState::STOPPED);  // stop intaking
    Pose newPose = Chassis::getRobotPose();                 // New Pose is [24, 24, 90]
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
    // Initalize all robot subsystems
    Chassis::initialize();
    Scorer::initialize();

    while (true) {
        // Subsystem update will manipulate internal state from controller input
        Chassis::update();
        Scorer::update();

        // Subsystem act will apply internal state to the robot
        Chassis::act();
        Scorer::act();

        pros::delay(10);
    }
}
