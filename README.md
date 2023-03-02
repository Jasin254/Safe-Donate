# Safe-Donate
Smart Wearable Watch to monitor Vital Signs
Wearable Vital Sign Monitor
This is an open-source project for a wearable device that monitors vital signs such as heart rate and blood oxygen levels. The device is designed to be worn like a watch and communicates with a mobile phone via Bluetooth or WiFi to store and display data.

Features
Measures heart rate and blood oxygen levels
Displays data on a screen using a bar graph
Includes a battery management system to monitor and display battery status
Supports communication with a mobile phone via Bluetooth and WiFi
Sends data to Google Firebase for remote storage and access
Includes a warning system to alert users of abnormal vital sign measurements
Getting Started
Hardware Requirements
ESP32 or ESP8266 microcontroller
MAX30102 pulse oximeter and heart rate sensor
OLED display
Battery management system (e.g. TP4056 module)
Battery (e.g. 3.7V Li-ion battery)
Bluetooth or WiFi module (e.g. HC-05 or ESP8266)
Software Requirements
Arduino IDE
ESP32 or ESP8266 board support for Arduino IDE
MAX30102 library for Arduino IDE
Adafruit GFX and SSD1306 libraries for Arduino IDE
Firebase library for Arduino IDE
Installation
Connect the hardware components as shown in the circuit diagram.
Install the required libraries in Arduino IDE.
Upload the code to the microcontroller using Arduino IDE.
Connect the mobile phone to the device via Bluetooth or WiFi to view data and receive alerts.
Contributing
Contributions are welcome! If you would like to contribute to this project, please fork the repository and submit a pull request with your changes. You can also submit issues if you encounter any problems or have any suggestions for improvements.

License
This project is licensed under the MIT License - see the LICENSE file for details.
