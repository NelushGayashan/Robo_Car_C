#include "IRSensorArray.h"
#include <reg51.h> // Include 8051 register definitions

IRSensorArray::IRSensorArray(unsigned char pins[], unsigned char size)
    : pins(pins), size(size)
{
    // Initialize sensor pins as input
    for (unsigned char i = 0; i < size; ++i)
    {
        P0 &= ~(1 << pins[i]); // Set pin as input on port P0
    }
}

int IRSensorArray::read()
{
    int data = 0;
    for (unsigned char i = 0; i < size; ++i)
    {
        data <<= 1;
        data |= (P0 >> pins[i]) & 1; // Read pin state
    }
    return data;
}
