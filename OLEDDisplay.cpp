#include <reg51.h> // Ensure this file is correct for 8051 Micro Controller

// Define I2C pins using bitwise operations
#define I2C_SDA (P1 & 0x01) // SDA pin at bit 0 of Port 1
#define I2C_SCL (P1 & 0x02) // SCL pin at bit 1 of Port 1
#define OLED_ADDRESS 0x3C

// Define I2C communication functions
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char data);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(void);
void I2C_SendNack(void);

// OLED display initialization sequence
class OLEDDisplay
{
public:
    OLEDDisplay();
    void begin();
    void clear();
    void display();
    void print(const char *text);

private:
    void sendCommand(unsigned char command);
    void sendData(unsigned char data);
    unsigned char *getFontData(char c);
    unsigned char displayBuffer[128][8];
    unsigned char currentColumn;
};

OLEDDisplay::OLEDDisplay()
{
    // Initialize display buffer
    for (unsigned char i = 0; i < 128; ++i)
    {
        for (unsigned char j = 0; j < 8; ++j)
        {
            displayBuffer[i][j] = 0;
        }
    }
    currentColumn = 0;
}

void OLEDDisplay::begin()
{
    // Initialize the display
    sendCommand(0xAE); // Display OFF
    sendCommand(0xD5); // Set Display Clock Divide Ratio / Oscillator Frequency
    sendCommand(0x80); // Suggested ratio
    sendCommand(0xA8); // Set Multiplex Ratio
    sendCommand(0x3F); // 64MUX
    sendCommand(0xD3); // Set Display Offset
    sendCommand(0x00); // No offset
    sendCommand(0x40); // Set Display Start Line
    sendCommand(0x8D); // Charge Pump Setting
    sendCommand(0x14); // Enable Charge Pump
    sendCommand(0xA1); // Set Segment Re-map
    sendCommand(0xC8); // Set COM Output Scan Direction
    sendCommand(0xDA); // Set COM Pins Hardware Configuration
    sendCommand(0x12); // Alternative COM Pin Configuration
    sendCommand(0x81); // Set Contrast Control
    sendCommand(0x7F); // Default contrast
    sendCommand(0xA4); // Disable Entire Display On
    sendCommand(0xA6); // Set Normal Display
    sendCommand(0xAF); // Display ON
}

void OLEDDisplay::clear()
{
    // Clear the display buffer
    for (unsigned char i = 0; i < 128; ++i)
    {
        for (unsigned char j = 0; j < 8; ++j)
        {
            displayBuffer[i][j] = 0;
        }
    }
}

void OLEDDisplay::display()
{
    // Update the display with the buffer
    for (unsigned char page = 0; page < 8; ++page)
    {
        sendCommand(0xB0 + page); // Set page address
        sendCommand(0x00);        // Set lower column address
        sendCommand(0x10);        // Set higher column address

        for (unsigned char col = 0; col < 128; ++col)
        {
            sendData(displayBuffer[col][page]);
        }
    }
}

void OLEDDisplay::print(const char *text)
{
    // Print text to the display (example implementation)
    unsigned char i = 0;
    while (text[i] != '\0')
    {
        unsigned char *fontData = getFontData(text[i]);
        for (unsigned char col = 0; col < 8; ++col)
        {
            for (unsigned char page = 0; page < 8; ++page)
            {
                displayBuffer[currentColumn][page] = fontData[col + page * 8];
            }
        }
        currentColumn += 8;
        i++;
    }
}

void OLEDDisplay::sendCommand(unsigned char command)
{
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS << 1); // Send OLED address with write bit
    I2C_SendByte(0x00);              // Control byte for command
    I2C_SendByte(command);           // Send the command byte
    I2C_Stop();
}

void OLEDDisplay::sendData(unsigned char data)
{
    I2C_Start();
    I2C_SendByte(OLED_ADDRESS << 1); // Send OLED address with write bit
    I2C_SendByte(0x40);              // Control byte for data
    I2C_SendByte(data);              // Send the data byte
    I2C_Stop();
}

unsigned char *OLEDDisplay::getFontData(char c)
{
    static unsigned char fontData[8];
    // Fill fontData with actual font data
    const unsigned char font8x8[95][8] = {
        {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Space
        // Add more character data here
    };

    if (c >= 32 && c <= 126)
    { // Printable ASCII range
        unsigned char index = c - 32;
        for (unsigned char i = 0; i < 8; ++i)
        {
            fontData[i] = font8x8[index][i];
        }
    }
    else
    {
        // Default to blank character for non-printable characters
        for (unsigned char i = 0; i < 8; ++i)
        {
            fontData[i] = 0;
        }
    }

    return fontData;
}

// I2C Communication Functions

void I2C_Start(void)
{
    P1 |= 0x01;  // Set SDA high
    P1 |= 0x02;  // Set SCL high
    P1 &= ~0x01; // Pull SDA low
    P1 &= ~0x02; // Pull SCL low
}

void I2C_Stop(void)
{
    P1 &= ~0x01; // Set SDA low
    P1 |= 0x02;  // Set SCL high
    P1 |= 0x01;  // Set SDA high
}

void I2C_SendByte(unsigned char data)
{
    for (unsigned char i = 0; i < 8; ++i)
    {
        if (data & 0x80)
        {
            P1 |= 0x01; // Set SDA high
        }
        else
        {
            P1 &= ~0x01; // Set SDA low
        }
        P1 |= 0x02; // Set SCL high
        data <<= 1;
        P1 &= ~0x02; // Set SCL low
    }
    P1 |= 0x01;  // Release bus for ACK
    P1 |= 0x02;  // Set SCL high
    P1 &= ~0x02; // Set SCL low
}

unsigned char I2C_ReceiveByte(void)
{
    unsigned char data = 0;
    for (unsigned char i = 0; i < 8; ++i)
    {
        P1 |= 0x02; // Set SCL high
        data <<= 1;
        if (P1 & 0x01)
        {
            data |= 1;
        }
        P1 &= ~0x02; // Set SCL low
    }
    return data;
}

void I2C_SendAck(void)
{
    P1 &= ~0x01; // Set SDA low
    P1 |= 0x02;  // Set SCL high
    P1 &= ~0x02; // Set SCL low
}

void I2C_SendNack(void)
{
    P1 |= 0x01;  // Set SDA high
    P1 |= 0x02;  // Set SCL high
    P1 &= ~0x02; // Set SCL low
}
