#ifndef ROBOT_H
#define ROBOT_H

#include "IRSensorArray.h"
#include "MotorController.h"
#include "UltrasonicSensor.h"
#include "Gripper.h"
#include "OLEDDisplay.h"

class Robot
{
public:
    Robot(IRSensorArray &irArray, MotorController &motorCtrl, UltrasonicSensor &ultrasonic, Gripper &gripper, OLEDDisplay &display);
    void run();

private:
    IRSensorArray &irArray;
    MotorController &motorCtrl;
    UltrasonicSensor &ultrasonic;
    Gripper &gripper;
    OLEDDisplay &display;
    void delay(unsigned int ms); // Helper function for delay
};

#endif // ROBOT_H
