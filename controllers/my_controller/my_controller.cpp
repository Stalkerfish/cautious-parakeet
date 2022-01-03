// File:          my_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

#define MAX_SPEED 6.28
#define TIME_STEP 64

// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

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
