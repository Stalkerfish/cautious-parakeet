#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

#define MAX_SPEED 6.28
#define TIME_STEP 64

// All the webots classes are defined in the "webots" namespace
using namespace webots;
 int main(int argc, char **argv) {
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  Motor *left_motor = robot->getMotor("left wheel motor");
  Motor *right_motor = robot->getMotor("right wheel motor");

  left_motor->setPosition(INFINITY);
  right_motor->setPosition(INFINITY);

  left_motor->setVelocity(0.0);
  right_motor->setVelocity(0.0);

  double left_speed = MAX_SPEED;
  double right_speed = MAX_SPEED;

  DistanceSensor *left_ir = robot->getDistanceSensor("ir0");
  DistanceSensor *right_ir = robot->getDistanceSensor("ir1");

  left_ir->enable(TIME_STEP);
  right_ir->enable(TIME_STEP);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
  while (robot->step(TIME_STEP) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();
    double left_ir_val = left_ir->getValue();
    double right_ir_val = right_ir->getValue();

    // Process sensor data here.
    left_speed = MAX_SPEED;
    right_speed = MAX_SPEED;

    bool line_left = (4 < left_ir_val) && (left_ir_val < 15);
    bool line_right = (4 < right_ir_val) && (right_ir_val < 15);

    // If line on left, drive left
    if ((left_ir_val > right_ir_val) && line_left){
	left_speed = MAX_SPEED * 0.25;
    }
    else if ((right_ir_val > left_ir_val) && line_right){
	right_speed = MAX_SPEED * 0.25;
    }

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
  };

  // Enter here exit cleanup code.
  delete robot;
  return 0;
}
}
