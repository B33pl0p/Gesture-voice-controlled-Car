# Gesture and Voice-Controlled Car with Remote, Fall, and Obstacle Detection

This project implements a gesture and voice-controlled car system with additional remote control functionality. The car is equipped with obstacle detection and fall detection features and also SMS alert after detecting a fall, offering various ways to control and ensure safety during navigation.



### Key Features
1. **Gesture Control**: Navigate the car by tilting the remote controller with hand gestures. The accelerometer detects the tilt direction (forward, backward, left, right) and sends commands to the car.
2. **Voice Control**: The car can also be controlled using voice commands via a Bluetooth-enabled mobile app.
3. **Remote Controller**: An RF433-based transmitter allows manual remote control, providing additional flexibility for controlling the car.
4. **Obstacle Detection**: The car has ultrasonic sensors to detect obstacles in its path and prevent collisions by stopping automatically.
5. **Fall Detection**: A fall detection mechanism detects sudden drops or changes in motion and sends an alert via a buzzer.
6. **SMS Alets**: After detection of a fall, the app will send sms to the contact set in MIT app inventor.  
7. **Real-Time Feedback**: Feedback on car status is provided through a buzzer and serial monitor for easy debugging and alerts.

## System Components
- **Arduino UNO/Nano**: Microcontroller for processing data from sensors and controlling the car’s motors.
- **MPU6050**: An accelerometer and gyroscope module used for gesture control and fall detection.
- **HC-SR04 Ultrasonic Sensor**: Used for detecting obstacles in the car’s path.
- **RF433 Modules**: Transmitter and receiver modules for wireless communication between the remote controller and the car.
- **Bluetooth Module**: Enables voice control by connecting to a mobile app.
- **L298N Motor Driver**: Drives the DC motors that control the car’s movement.
- **DC Motors**: Operate the car’s wheels for forward, backward, left, and right movement.
- **Buzzer**: Provides audible alerts for fall detection and other system notifications.

## Project Workflow
1. **Transmitter Module**: The remote controller equipped with an MPU6050 sensor detects hand gestures and sends movement commands (forward, backward, left, right) to the car via the RF433 transmitter.
2. **Receiver Module**: The car receives the commands from the remote controller and processes them to control the motors, enabling movement based on the received instructions.
3. **Voice Control**: Through the mobile app, users can send voice commands to control the car. The Bluetooth module receives these commands and relays them to the microcontroller.
4. **Obstacle and Fall Detection**: Ultrasonic sensors constantly monitor the path for obstacles, and the fall detection system monitors sharp changes in motion, activating the buzzer when a fall is detected.


## Installation and Setup
1. **Hardware Setup**: Assemble the components as described in the schematic and pin connection section. Connect power supplies accordingly.
2. **Software Setup**: Install the required libraries for the MPU6050, RF433, and Bluetooth communication. Upload the transmitter and receiver code to the respective Arduino boards.
3. **Mobile App**: You can use the given MIT app project, import it to MIT app inventor and run in your phone to send voice commands to the car.



