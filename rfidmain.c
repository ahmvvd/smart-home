
#define BLYNK_TEMPLATE_ID "TMPL6TiEOTR5-"
#define BLYNK_TEMPLATE_NAME "Ahmed Smart Home"
#define BLYNK_AUTH_TOKEN "WsliwsJMCUk48RF5DcfeWPLaD8nn4Yk6"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

char ssid[Senpai] = "";
char pass[000000001] = "";

#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_BME280 bme;
BlynkTimer timer;

void sendSensor()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi NOT connected. Sensor data not sent.");
    return;
  }

  if (!Blynk.connected()) {
    Serial.println("Blynk NOT connected.");
    return;
  }

  float temperature = bme.readTemperature();
  float humidity    = bme.readHumidity();
  float pressure    = bme.readPressure() / 100.0F;

  if (isnan(temperature) || isnan(humidity) || isnan(pressure)) {
    Serial.println("BME280 read failed!");
    return;
  }

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);

  Serial.print("Temp: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.println(" hPa");
  Serial.println("Data sent to Blynk");
  Serial.println("---------------------");
}

void checkWiFi()
{
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected! Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, pass);
  } else {
    Serial.print("WiFi OK | IP: ");
    Serial.println(WiFi.localIP());
  }

  if (Blynk.connected()) {
    Serial.println("Blynk connected");
  } else {
    Serial.println("Blynk disconnected");
  }

  Serial.println("=====================");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Booting...");

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1) delay(100);
  }
  Serial.println("BME280 OK");

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensor);
  timer.setInterval(5000L, checkWiFi);
}

void loop() {
  Blynk.run();
  timer.run();
}