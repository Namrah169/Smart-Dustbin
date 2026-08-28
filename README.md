# Smart Dustbin

# IoT Based Smart Dustbin using ESP32 and Blynk

 📌 **About the Project**

We developed this Smart Dustbin as a group project to explore how IoT and sensors can be used to make a normal dustbin smarter and more convenient.

The project uses an ESP32 as the main controller. Different sensors and modules are connected to the ESP32 to control the lid, monitor the garbage level, display information, and provide the dustbin's location.

We also used the Blynk IoT platform for remote monitoring and control.

🎯 **Objectives**

- Automatically open and close the dustbin lid.
- Detect human/object presence using an IR sensor.
- Monitor the garbage fill level.
- Display the fill percentage on an LCD.
- Monitor the dustbin through Blynk.
- Get the dustbin location using GPS.
- Provide automatic and manual lid control.

 **Components Used**

- ESP32 – Main microcontroller
- Ultrasonic Sensor – Measures the garbage level
- IR Sensor – Detects human/object presence
- Servo Motor – Opens and closes the lid
- 16×2 LCD – Displays fill percentage and lid status
- I2C – Used for LCD communication
- GPS Module – Provides location information
- Blynk – Used for IoT monitoring and control

**How It Works**

The ESP32 controls all the components of the Smart Dustbin.

When a person or object comes near the dustbin, the IR sensor detects it and the servo motor opens the lid automatically.

The ultrasonic sensor measures the distance between the sensor and the garbage. This distance is used to calculate the approximate fill percentage.

The LCD displays the fill percentage and lid status.

The ESP32 is connected to Wi-Fi and communicates with the Blynk platform. The Blynk dashboard shows the fill percentage, lid status, latitude, and longitude. It also provides automatic and manual lid control.

When the dustbin becomes highly filled, an alert can be generated through Blynk.

 **Blynk Dashboard**

We used Blynk as the IoT platform for monitoring and controlling our Smart Dustbin.

The dashboard includes:

- Fill Percentage
- Lid Status
- Latitude
- Longitude
- Automatic Control
- Manual Lid Control

A screenshot of our Blynk dashboard is included in this repository.

**Features**

- Automatic lid opening and closing
- Human/object detection
- Garbage fill-level monitoring
- LCD display
- GPS location
- Blynk monitoring
- Automatic and manual control
- Full-bin alert

**Source Code**

The ESP32 source code is available in:

**Smart_Dustbin.ino**

The code contains the logic for the sensors, servo motor, LCD, GPS module, and Blynk communication.

For security, actual Wi-Fi passwords and Blynk authentication credentials should not be shared publicly.

**Circuit Diagram**

The circuit diagram shows the connections between the ESP32, ultrasonic sensor, IR sensor, servo motor, LCD, and GPS module.

The circuit diagram is included in this repository.

**Project Photos**

This repository contains photos of our Smart Dustbin hardware and Blynk dashboard.

 **Project Demo**

A working/demo video of the Smart Dustbin is also included in this repository.

**Project Type**

This was a **group project**. We worked together on the design, hardware setup, coding, testing, and presentation of the Smart Dustbin.

 **Technologies Used**

- ESP32
- Arduino / C++
- Blynk IoT
- Ultrasonic Sensor
- IR Sensor
- GPS Module
- Servo Motor
- 16×2 LCD
- I2C

 **Future Improvements**

In the future, the project can be improved by adding better waste-level tracking, storing historical data, improved notifications, and connecting multiple smart dustbins to a centralized monitoring system.

 **Learning**

This project helped us understand how sensors, microcontrollers, IoT platforms, and different hardware components can work together to solve a real-world problem.

**Conclusion**

Our Smart Dustbin project was a practical way to learn about IoT and embedded systems. By combining ESP32, sensors, GPS, servo motor, LCD, and Blynk, we developed a system that can automatically control the lid and monitor useful information about the dustbin.
