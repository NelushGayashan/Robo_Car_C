#include "UltrasonicSensor.h"
#include <reg51.h> // Include 8051 register definitions

#define TRIGGER_PIN (1 << 0) // Pin 0 of Port 0 for Trigger
#define ECHO_PIN (1 << 1)    // Pin 1 of Port 0 for Echo

UltrasonicSensor::UltrasonicSensor(unsigned char triggerPin, unsigned char echoPin)
    : triggerPin(triggerPin), echoPin(echoPin)
{
    // Initialize sensor pins
    P0 &= ~echoPin;   // Set echo pin as input 
    P0 |= triggerPin; // Set trigger pin as output
}

int UltrasonicSensor::measureDistance()
{
    unsigned int pulseWidth = 0;

    // Trigger the ultrasonic sensor
    P0 &= ~triggerPin;     // Low
    delayMicroseconds(2);  // Short delay
    P0 |= triggerPin;      // High
    delayMicroseconds(10); // Short delay
    P0 &= ~triggerPin;     // Low

    // Measure the duration of the echo pulse
    while ((P0 & echoPin) == 0)
        ; // Wait for echo start
    while ((P0 & echoPin) != 0)
    { // Wait for echo end
        pulseWidth++;
        delayMicroseconds(1); // Small delay for pulse width measurement
    }


    // Calculate distance in cm
    return pulseWidth / 58; // Convert pulse width to distance
}

void UltrasonicSensor::delayMicroseconds(unsigned int us)
{

    // Number of iterations to achieve approximately 1 microsecond delay
    const unsigned int delayPerMicrosecond = 10; // This value should be calibrated

    while (us-- > 0)
    {
        unsigned int i = delayPerMicrosecond;
        while (i-- > 0)
        {
            // Empty loop for delay
        }
    }
}

