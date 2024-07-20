#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <reg51.h> // Include 8051 register definitions

class OLEDDisplay
{
public:
    OLEDDisplay();                // Constructor
    void begin();                 // Initialize the display
    void clear();                 // Clear the display
    void display();               // Update the display
    void print(const char *text); // Print text to the display

private:
    void sendCommand(unsigned char command); // Send a command to the OLED display
    void sendData(unsigned char data);       // Send data to the OLED display
    unsigned char *getFontData(char c);      // Get font data for a character
    unsigned char displayBuffer[128][8];     // Display buffer
    unsigned char currentColumn;             // Current column position
};

#endif // OLED_DISPLAY_H
