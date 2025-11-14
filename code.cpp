// Blynk Credentials (MUST be defined FIRST, before any includes)
#define BLYNK_TEMPLATE_ID "TMPL3K8aRdaTC"
#define BLYNK_TEMPLATE_NAME "health monitoring system"
#define BLYNK_AUTH_TOKEN "c7pZjjFBt_IwyW_-C35e3hPSCYc-Aagp"

// Now include libraries
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <BlynkSimpleEsp8266.h>

// WiFi Credentials
const char* ssid = "Priya's A22";
const char* password = "qpxw5049";

// ThingSpeak Settings
const char* server = "api.thingspeak.com";
String apiKey = "2FMJLCWV9ZNTD1UQ";

// Pin Definitions
#define DHTPIN D4          // DHT11 data pin
#define HEARTBEAT_PIN A0   // KY-039 signal pin
#define LED_HEARTBEAT D1   // Optional: Heartbeat indicator LED
#define LED_SEND D2        // Optional: Data transmission LED

// Sensor Settings
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variables
int heartbeatValue = 0;
int heartbeatBPM = 0;
float temperature = 0;
float humidity = 0;
unsigned long lastUpdate = 0;
const long updateInterval = 15000; // Update every 15 seconds

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Initialize pins
  pinMode(LED_HEARTBEAT, OUTPUT);
  pinMode(LED_SEND, OUTPUT);

  // Initialize sensors
  dht.begin();

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  Serial.println("Blynk initialized");
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read sensors
  readHeartbeat();
  readTemperatureHumidity();

  // Send data to Blynk
  Blynk.virtualWrite(V1, heartbeatBPM);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);

  // Send data to ThingSpeak every 15 seconds
  if (millis() - lastUpdate > updateInterval) {
    sendToThingSpeak();
    lastUpdate = millis();
  }

  delay(100);
}

void readHeartbeat() {
  // Read analog value from KY-039
  heartbeatValue = analogRead(HEARTBEAT_PIN);

  // Simple BPM calculation (needs calibration)
  // This is a basic approach - for accurate BPM, implement peak detection
  heartbeatBPM = map(heartbeatValue, 0, 1024, 60, 100);

  // Blink LED with heartbeat
  if (heartbeatValue > 512) {
    digitalWrite(LED_HEARTBEAT, HIGH);
  } else {
    digitalWrite(LED_HEARTBEAT, LOW);
  }

  Serial.print("Heartbeat Value: ");
  Serial.print(heartbeatValue);
  Serial.print(" | BPM: ");
  Serial.println(heartbeatBPM);
}

void readTemperatureHumidity() {
  // Read DHT11 sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
}

void sendToThingSpeak() {
  if (client.connect(server, 80)) {
    digitalWrite(LED_SEND, HIGH);

    // Create data string
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(heartbeatBPM);
    postStr += "&field2=";
    postStr += String(temperature);
    postStr += "&field3=";
    postStr += String(humidity);
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

    Serial.println("Data sent to ThingSpeak!");

    digitalWrite(LED_SEND, LOW);
  } else {
    Serial.println("Connection to ThingSpeak failed!");
  }
  client.stop();
}
