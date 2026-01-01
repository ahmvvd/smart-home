# smart-home
 Hardware Used

ESP32 Development Board

MFRC522 RFID Reader

BME280 Sensor (Temperature, Humidity, Pressure)

Wi-Fi Network

Blynk IoT Platform

Communication Protocols

SPI (MOSI, MISO, SCK, SS)
Used for communication between the ESP32 and the MFRC522 RFID reader.

I²C (SDA, SCL)
Used for communication between the ESP32 and the BME280 environmental sensor.

System Functionality

Detects and reads RFID card UID via MFRC522

Measures temperature (°C), humidity (%), and pressure (hPa) using BME280

Displays data on the Serial Monitor

Sends environmental data to the Blynk cloud dashboard via Wi-Fi

Blynk Cloud Setup

Create a project in the Blynk IoT App

Select ESP32 as the device

Copy the Template ID, Template Name, and Auth Token

Add widgets (e.g., Gauge or Display) and assign Virtual Pins

Connect ESP32 to Wi-Fi and upload the code

Software & Libraries

Arduino IDE

ESP32 Board Package

SPI, Wire (I²C)

MFRC522 Library

Adafruit BME280 Library

Blynk Library

Applications

Smart access control systems

IoT-based environmental monitoring

Smart homes and smart buildings
