# Robot Control System

## Overview

The Robot Control System is designed to control a robotic vehicle using various sensors and components. It integrates an IR sensor array for line following, a motor controller for movement, an ultrasonic sensor for distance measurement, a gripper for object manipulation, and an OLED display for user feedback.

## Features

- **Line Following**: Uses an IR sensor array to detect and follow a line.
- **Obstacle Avoidance**: Utilizes an ultrasonic sensor to detect obstacles and avoid collisions.
- **Object Manipulation**: Controls a gripper to pick up and manipulate objects.
- **User Feedback**: Displays sensor readings and status on an OLED display.

## Components

- **IR Sensor Array**: Detects the line for following.
- **Motor Controller**: Manages the movement of the robot.
- **Ultrasonic Sensor**: Measures distance to detect obstacles.
- **Gripper**: Moves to pick up or manipulate objects.
- **OLED Display**: Shows sensor readings and status information.

## Installation

1. **Clone the Repository**

    ```bash
    git clone https://github.com/yourusername/robot-control-system.git
    ```

2. **Set Up the Environment**

    Ensure you have the necessary tools and libraries installed. This project is developed for the 8051 microcontroller using standard C.

3. **Compile the Code**

    Use a compatible compiler for the 8051 microcontroller to compile the source code. Make sure to configure the compiler with the appropriate settings for your hardware.

## Usage

1. **Connect the Components**

    - Connect the IR sensor array to the specified pins on the microcontroller.
    - Connect the motor controller, ultrasonic sensor, gripper, and OLED display as per the hardware specifications.

2. **Run the Robot**

    Once the components are connected and the code is uploaded to the microcontroller, the robot will start operating based on the sensor inputs. It will follow a line, avoid obstacles, manipulate objects, and display relevant information on the OLED screen.

## Code Structure

- `Robot.h`: Header file for the Robot class.
- `Robot.cpp`: Implementation of the Robot class.
- `IRSensorArray.h` and `IRSensorArray.cpp`: Handle the IR sensor array functionalities.
- `MotorController.h` and `MotorController.cpp`: Manage motor controls.
- `UltrasonicSensor.h` and `UltrasonicSensor.cpp`: Interface with the ultrasonic sensor.
- `Gripper.h` and `Gripper.cpp`: Control the gripper.
- `OLEDDisplay.h` and `OLEDDisplay.cpp`: Interface with the OLED display.

## Example Code

Here is a brief example of how to use the `Robot` class:

```cpp
#include "Robot.h"
#include "IRSensorArray.h"
#include "MotorController.h"
#include "UltrasonicSensor.h"
#include "Gripper.h"
#include "OLEDDisplay.h"

// Initialize components
IRSensorArray irArray(/* IR sensor pins */);
MotorController motorCtrl(/* Motor pins */);
UltrasonicSensor ultrasonic(/* Trigger pin */, /* Echo pin */);
Gripper gripper(/* Gripper pins */);
OLEDDisplay display(/* OLED pins */);

// Create Robot instance
Robot robot(irArray, motorCtrl, ultrasonic, gripper, display);

// Run the robot
int main() {
    robot.run();
    return 0;
}
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that you follow the coding standards and include relevant tests.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
