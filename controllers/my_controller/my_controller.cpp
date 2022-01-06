#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>

#define MAX_SPEED 6.28
#define TIME_STEP 64

using namespace webots;
 int main(int argc, char **argv) {
  Robot *robot = new Robot();

  int timeStep = (int)robot->getBasicTimeStep();

  Motor *left_motor = robot->getMotor("left wheel motor");
  Motor *right_motor = robot->getMotor("right wheel motor");

  left_motor->setPosition(INFINITY);
  right_motor->setPosition(INFINITY);

  left_motor->setVelocity(0.0);
  right_motor->setVelocity(0.0);

  double left_speed = MAX_SPEED;
  double right_speed = MAX_SPEED;

  DistanceSensor *right_ir = robot->getDistanceSensor("ir0");
  DistanceSensor *left_ir = robot->getDistanceSensor("ir1");

  left_ir->enable(TIME_STEP);
  right_ir->enable(TIME_STEP);

  //Main loop:
  while (robot->step(timeStep) != -1) {
  while (robot->step(TIME_STEP) != -1) {
    
    double left_ir_val = left_ir->getValue();
    double right_ir_val = right_ir->getValue();
    
    std::cout << "Valor do sensor esquerdo: " << left_ir_val << std::endl;
    std::cout << "Valor do sensor direito: " << right_ir_val << std::endl;
    
    left_speed = MAX_SPEED;
    right_speed = MAX_SPEED;

    bool line_left = (4 < left_ir_val) && (left_ir_val < 15);
    bool line_right = (4 < right_ir_val) && (right_ir_val < 15);

    if ((left_ir_val > right_ir_val) && line_left){
	left_speed = MAX_SPEED * 0.25;
    }
    else if ((right_ir_val > left_ir_val) && line_right){
	right_speed = MAX_SPEED * 0.25;
    }

    left_motor->setVelocity(left_speed);
    right_motor->setVelocity(right_speed);
  }

  delete robot;
  return 0;
}
}
