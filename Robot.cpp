#include "Robot.h"
#include <reg51.h> // Include 8051 register definitions
#include <stdio.h> // For sprintf function

Robot::Robot(IRSensorArray &irArray, MotorController &motorCtrl, UltrasonicSensor &ultrasonic, Gripper &gripper, OLEDDisplay &display)
    : irArray(irArray), motorCtrl(motorCtrl), ultrasonic(ultrasonic), gripper(gripper), display(display)
{
}

void Robot::run()
{
    int distance;
    int lineFollowing;
    char buffer[32]; // Buffer for converting integers to strings

    while (1)
    {
        lineFollowing = irArray.read();
        distance = ultrasonic.measureDistance();

        if (distance > 0 && distance < 10)
        {
            gripper.move();
            motorCtrl.moveForward();
        }
        else if (lineFollowing == 0b011000)
        {
            motorCtrl.stop();
            motorCtrl.turnRight();
        }
        else
        {
            motorCtrl.moveForward();
        }

        // Display sensor readings on OLED display
        display.clear();

        // Convert integers to strings and print them
        sprintf(buffer, "Line Following: %d", lineFollowing);
        display.print(buffer);
        display.print("\n");

        sprintf(buffer, "Distance: %d", distance);
        display.print(buffer);

        display.display();

        delay(1000); // Delay for 1 second
    }
}

void Robot::delay(unsigned int ms)
{
    // Simple delay function
    unsigned int i, j;
    for (i = 0; i < ms; ++i)
    {
        for (j = 0; j < 1275; ++j)
        {
            // Delay loop
        }
    }
}
