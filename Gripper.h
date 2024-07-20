#ifndef GRIPPER_H
#define GRIPPER_H

class Gripper
{
public:
    Gripper(unsigned char pin);
    void move();

private:
    unsigned char pin;
    void delay(unsigned int ms); // Helper function for delay
};

#endif // GRIPPER_H
