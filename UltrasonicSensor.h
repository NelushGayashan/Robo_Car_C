#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

class UltrasonicSensor
{
public:
    UltrasonicSensor(unsigned char triggerPin, unsigned char echoPin);
    int measureDistance();

private:
    unsigned char triggerPin;
    unsigned char echoPin;
    void delayMicroseconds(unsigned int us); // Helper function for microsecond delay
};

#endif // ULTRASONICSENSOR_H
