#include <SPI.h>
#include <MFRC522.h>
// #include <ESP32Servo.h>     // ERROR FIX: causes compilation error with ESP32 core 3.x
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SS_PIN 7      // SDA
#define RST_PIN 21
#define SERVO_PIN 2
#define SDA_PIN 8
#define SCL_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
// Servo gateServo;            // ERROR FIX: servo not used, library removed
Adafruit_BME280 bme;          // I2C

void setup() {
  Serial.begin(115200);
  while (!Serial);            // ERROR FIX: moved inside setup correctly

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280 sensor!");
    while (1) delay(100);
  }

  Serial.println("BME280 sensor Found!");

  float tempreture = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  Serial.println(tempreture);
  Serial.println(humidity);
  Serial.println(pressure);

  SPI.begin(4, 5, 6, 7);      // unchanged
  mfrc522.PCD_Init();

  Serial.println("Scan an RFID tag...");
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Tag UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  mfrc522.PICC_HaltA();
}