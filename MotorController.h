#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

class MotorController
{
public:
    MotorController(unsigned char pins[], unsigned char size);
    void moveForward();
    void stop();
    void turnRight();

private:
    unsigned char *pins;
    unsigned char size;
    void delay(unsigned int ms); // Helper function for delay
};

#endif // MOTORCONTROLLER_H
