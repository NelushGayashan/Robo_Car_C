#include "Gripper.h"
#include <reg51.h> // Include 8051 register definitions

Gripper::Gripper(unsigned char pin) : pin(pin)
{
    // Initialize pin as output
    P1 |= (1 << pin); // Set pin to output mode on port P1
}

void Gripper::move()
{
    // Control the gripper
    P1 |= (1 << pin);  // Set pin high to activate the gripper
    delay(500);        // Delay for 500 milliseconds to simulate gripper action
    P1 &= ~(1 << pin); // Set pin low to deactivate the gripper
}

#include <reg51.h> // Include 8051 register definitions

void delay(unsigned int ms)
{
    unsigned int i, j;
    unsigned int innerLoopCount = 900; 

    for (i = 0; i < ms; ++i)
    {
        for (j = 0; j < innerLoopCount; ++j)
        {
            // Simple delay loop
        }
    }
}
