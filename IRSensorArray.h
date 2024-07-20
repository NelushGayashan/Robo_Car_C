#ifndef IRSENSORARRAY_H
#define IRSENSORARRAY_H

class IRSensorArray
{
public:
    IRSensorArray(unsigned char pins[], unsigned char size);
    int read();

private:
    unsigned char *pins;
    unsigned char size;
};

#endif // IRSENSORARRAY_H
