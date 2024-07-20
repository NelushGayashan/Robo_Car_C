#include "MotorController.h"
#include <reg51.h> // Include 8051 register definitions

MotorController::MotorController(unsigned char pins[], unsigned char size)
    : pins(pins), size(size)
{
    // Initialize motor pins as output
    for (unsigned char i = 0; i < size; ++i)
    {
        P2 |= (1 << pins[i]); // Set pin as output on port P2
    }
}

void MotorController::moveForward()
{
    // Set pins for forward movement
    P2 = 0x0F; // Setting forward direction (adjust as needed)
}

void MotorController::stop()
{
    // Stop motors
    P2 &= ~0x0F; // Clear the pins to stop motors
}

void MotorController::turnRight()
{
    // Set pins for turning right
    P2 = 0x01; // Turning right (adjust as needed)
}

void MotorController::delay(unsigned int ms)
{
    unsigned int i, j;
    // Adjust loop counts to approximate a 100ms delay
    for (i = 0; i < ms; ++i)
    {
        for (j = 0; j < 860; ++j) // Adjusted loop count
        {
            // Loop for delay
        }
    }
}
