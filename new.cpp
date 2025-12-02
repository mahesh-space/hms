/*
 * Health Monitoring System
 * Sensors: MAX30100 (Heart Rate & SpO2) + DS18B20 (Temperature)
 * Platforms: ThingSpeak + Blynk
 * 
 * Connections:
 * MAX30100:
 *   VCC -> 3.3V
 *   GND -> GND
 *   SDA -> D2 (GPIO4)
 *   SCL -> D1 (GPIO5)
 * 
 * DS18B20:
 *   VCC -> 3.3V
 *   GND -> GND
 *   DATA -> D3 (GPIO0) with 4.7K pull-up resistor to 3.3V
 * 
 * Required Libraries:
 * - MAX30100lib by OXullo Intersecans
 * - OneWire by Paul Stoffregen
 * - DallasTemperature by Miles Burton
 * - BlynkSimpleEsp8266
 */

// Blynk Credentials (MUST be defined FIRST, before any includes)
#define BLYNK_TEMPLATE_ID "TMPL3K8aRdaTC"
#define BLYNK_TEMPLATE_NAME "health monitoring system"
#define BLYNK_AUTH_TOKEN "c7pZjjFBt_IwyW_-C35e3hPSCYc-Aagp"

// Now include libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// WiFi Credentials
const char* ssid = "Girls hostel 7";
const char* password = "Nielit@123G";

// ThingSpeak Settings
const char* server = "api.thingspeak.com";
String apiKey = "2FMJLCWV9ZNTD1UQ";

// Pin Definitions
#define ONE_WIRE_BUS 0     // DS18B20 data pin (D3/GPIO0)
#define LED_HEARTBEAT D6   // Heartbeat indicator LED
#define LED_SEND D7        // Data transmission LED

// Setup sensors
PulseOximeter pox;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

// Variables
float heartRate = 0;
uint8_t spO2 = 0;
float bodyTemperature = 0;
unsigned long lastUpdate = 0;
unsigned long lastPoxUpdate = 0;
const long updateInterval = 15000;      // ThingSpeak update every 15 seconds
const long poxReportInterval = 1000;    // MAX30100 reading every 1 second

WiFiClient client;

// Callback when a heartbeat is detected
void onBeatDetected() {
  Serial.println("💓 Beat!");
  digitalWrite(LED_HEARTBEAT, HIGH);
  delay(50);
  digitalWrite(LED_HEARTBEAT, LOW);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("\n\n=================================");
  Serial.println("Health Monitoring System Starting");
  Serial.println("=================================");

  // Initialize pins
  pinMode(LED_HEARTBEAT, OUTPUT);
  pinMode(LED_SEND, OUTPUT);

  // Initialize I2C for MAX30100
  Wire.begin(4, 5); // SDA=D2(GPIO4), SCL=D1(GPIO5)

  // Initialize MAX30100
  Serial.print("Initializing MAX30100...");
  if (!pox.begin()) {
    Serial.println("FAILED!");
    Serial.println("Please check MAX30100 wiring");
  } else {
    Serial.println("SUCCESS!");
    pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
  }

  // Initialize DS18B20
  Serial.print("Initializing DS18B20...");
  tempSensor.begin();
  Serial.println("SUCCESS!");
  Serial.print("Found ");
  Serial.print(tempSensor.getDeviceCount());
  Serial.println(" temperature sensor(s)");

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < 20) {
    delay(500);
    Serial.print(".");
    wifiAttempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi connection failed!");
  }

  // Initialize Blynk
  Serial.print("Initializing Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println("SUCCESS!");

  Serial.println("\n=================================");
  Serial.println("System Ready!");
  Serial.println("=================================\n");
  
  lastUpdate = millis();
  lastPoxUpdate = millis();
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Update MAX30100 continuously (required for accurate readings)
  pox.update();

  // Read and report sensor data every second
  if (millis() - lastPoxUpdate > poxReportInterval) {
    readSensors();
    displayReadings();
    sendToBlynk();
    lastPoxUpdate = millis();
  }

  // Send data to ThingSpeak every 15 seconds
  if (millis() - lastUpdate > updateInterval) {
    sendToThingSpeak();
    lastUpdate = millis();
  }
}

void readSensors() {
  // Read MAX30100 (Heart Rate & SpO2)
  heartRate = pox.getHeartRate();
  spO2 = pox.getSpO2();

  // Read DS18B20 (Body Temperature)
  tempSensor.requestTemperatures();
  bodyTemperature = tempSensor.getTempCByIndex(0);
  
  // Validate temperature reading
  if (bodyTemperature == DEVICE_DISCONNECTED_C || bodyTemperature < 0 || bodyTemperature > 50) {
    Serial.println("Warning: Invalid temperature reading");
    bodyTemperature = 0;
  }
}

void displayReadings() {
  Serial.println("--- Sensor Readings ---");
  
  Serial.print("Heart Rate: ");
  if (heartRate > 0 && heartRate < 200) {
    Serial.print(heartRate, 1);
    Serial.print(" bpm");
  } else {
    Serial.print("-- (Place finger on sensor)");
  }
  
  Serial.print("  |  SpO2: ");
  if (spO2 > 0 && spO2 <= 100) {
    Serial.print(spO2);
    Serial.print(" %");
  } else {
    Serial.print("--");
  }
  
  Serial.print("  |  Body Temp: ");
  if (bodyTemperature > 0) {
    Serial.print(bodyTemperature, 1);
    Serial.println(" °C");
  } else {
    Serial.println("-- °C");
  }
  
  Serial.println();
}

void sendToBlynk() {
  // Send valid readings to Blynk
  if (heartRate > 0 && heartRate < 200) {
    Blynk.virtualWrite(V1, heartRate);  // Heart Rate to V1
  }
  
  if (spO2 > 0 && spO2 <= 100) {
    Blynk.virtualWrite(V2, spO2);       // SpO2 to V2
  }
  
  if (bodyTemperature > 0 && bodyTemperature < 50) {
    Blynk.virtualWrite(V3, bodyTemperature);  // Body Temperature to V3
  }
}

void sendToThingSpeak() {
  // Only send if we have valid readings
  if ((heartRate <= 0 || heartRate >= 200) && bodyTemperature <= 0) {
    Serial.println("Skipping ThingSpeak update - no valid data");
    return;
  }

  digitalWrite(LED_SEND, HIGH);
  
  if (client.connect(server, 80)) {
    // Create data string
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(heartRate > 0 && heartRate < 200 ? heartRate : 0);
    postStr += "&field2=";
    postStr += String(spO2 > 0 && spO2 <= 100 ? spO2 : 0);
    postStr += "&field3=";
    postStr += String(bodyTemperature > 0 ? bodyTemperature : 0);
    postStr += "\r\n\r\n";

    // Send data to ThingSpeak
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("✓ Data sent to ThingSpeak!");
    Serial.println("========================\n");
    
  } else {
    Serial.println("✗ ThingSpeak connection failed!");
  }
  
  client.stop();
  digitalWrite(LED_SEND, LOW);
}
