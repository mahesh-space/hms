

# 🩺 IoT-Based Health Monitoring System

### *NodeMCU ESP8266 + KY-039 + DHT11 + ThingSpeak + Blynk*

---

# 📚 **Table of Contents**

* [🔍 Project Overview](#-project-overview)
* [🛠 Components Required](#-components-required)
* [🔌 Circuit Wiring](#-circuit-wiring)
* [💻 Software Setup](#-software-setup)
* [☁ ThingSpeak Setup](#-thingspeak-setup)
* [📱 Blynk App Setup](#-blynk-app-setup)
* [📜 Code Configuration](#-code-configuration)
* [⬆️ Uploading Code](#️-uploading-code)
* [🧪 Testing Procedure](#-testing-procedure)
* [🐞 Troubleshooting](#-troubleshooting)
* [📊 System Workflow](#-system-workflow)
* [📜 License](#-license)

---

# 🔍 **Project Overview**

This IoT-based system measures:

* ❤️ **Heart Rate (BPM)** using KY-039
* 🌡️ **Temperature** using DHT11
* 💧 **Humidity** using DHT11
* 📤 Sends real-time data to **ThingSpeak Cloud**
* 📱 Displays live sensor data in **Blynk Mobile App**

The system is low-cost, portable, and ideal for remote patient monitoring.

---

# 🛠 **Components Required**

| Component                        | Qty |
| -------------------------------- | --- |
| NodeMCU ESP8266                  | 1   |
| KY-039 Heartbeat Sensor          | 1   |
| DHT11 Sensor                     | 1   |
| Breadboard                       | 1   |
| Jumper Wires                     | —   |
| LEDs + 220Ω Resistors (optional) | 2   |

---

# 🔌 **Circuit Wiring**

### **KY-039 → NodeMCU**

| Sensor Pin | NodeMCU Pin |
| ---------- | ----------- |
| VCC        | 3.3V        |
| GND        | GND         |
| SIGNAL     | A0          |

### **DHT11 → NodeMCU**

| DHT11 Pin | NodeMCU Pin |
| --------- | ----------- |
| VCC       | 3.3V        |
| GND       | GND         |
| DATA      | D4 (GPIO2)  |

### **Optional LEDs**

| LED Type      | NodeMCU Pin |
| ------------- | ----------- |
| Heartbeat LED | D1          |
| Data Send LED | D2          |

---

# 💻 **Software Setup**

### **Install Arduino IDE**

[https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

### **Install ESP8266 Board Package**

1. Arduino IDE → **Preferences**
2. Add this to *Boards Manager URLs*:

   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Tools → Board → Boards Manager → Install **ESP8266 by ESP8266 Community**

### **Select Board**

```
Tools → Board → NodeMCU 1.0 (ESP-12E)
```

### **Install Required Libraries**

* DHT sensor library (Adafruit)
* Adafruit Unified Sensor
* Blynk (IoT)
* ESP8266WiFi (built-in)

---

# ☁ **ThingSpeak Setup**

### 1. Create Account

[https://thingspeak.com](https://thingspeak.com)

### 2. Make New Channel

Enable fields:

* **Field1 → Heart Rate**
* **Field2 → Temperature**
* **Field3 → Humidity**

### 3. Copy the Write API Key

Paste it into your Arduino code.

### 4. Dashboard updates every 15 seconds automatically.

---

# 📱 **Blynk App Setup**

### 1. Install Blynk IoT App

(Android/iOS)

### 2. Create Template

```
Name: Health Monitor
Hardware: ESP8266
Connection: WiFi
```

### 3. Get Template Values

Inside template → **Info**:

* `BLYNK_TEMPLATE_ID`
* `BLYNK_TEMPLATE_NAME`
* `BLYNK_AUTH_TOKEN`

### 4. Add Datastreams

Go to **Datastreams → Virtual Pin**

| Datastream  | Type    | Pin |
| ----------- | ------- | --- |
| Heart Rate  | Integer | V1  |
| Temperature | Float   | V2  |
| Humidity    | Float   | V3  |

### 5. Add Widgets

* Gauge → V1
* Gauge → V2
* Label/Gauge → V3

---

# 📜 **Code Configuration**

### Add these at the top of your code:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Health Monitor"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
```

### Update WiFi & ThingSpeak:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
String apiKey = "YOUR_THINGSPEAK_WRITE_API_KEY";
```

### Send Data to Blynk:

```cpp
Blynk.virtualWrite(V1, heartbeatBPM);
Blynk.virtualWrite(V2, temperature);
Blynk.virtualWrite(V3, humidity);
```

---

# ⬆️ **Uploading Code**

1. Connect NodeMCU via USB
2. Select port:

   ```
   Tools → Port → /dev/cu.usbserial...
   ```
3. Click **Upload**
4. Open Serial Monitor @ **115200 baud**

Expected output:

```
WiFi connected
IP address: 192.168.x.x
Heartbeat Value: 350 | BPM: 82
Temperature: 29°C | Humidity: 54%
Data sent to ThingSpeak!
```

---

# 🧪 **Testing Procedure**

### ✔ Heartbeat Sensor

Place finger lightly on KY-039 → values fluctuate.
Heartbeat LED blinks (if connected).

### ✔ DHT11 Sensor

Serial print shows temperature & humidity.

### ✔ ThingSpeak

Channel graphs update every 15 seconds.

### ✔ Blynk App

All virtual values update live:

* V1 → BPM
* V2 → Temperature
* V3 → Humidity

---

# 🐞 **Troubleshooting**

### ❌ WiFi Not Connecting

* SSID/password wrong
* Must use **2.4 GHz WiFi**

### ❌ DHT11 shows “NaN”

* Wrong DATA pin
* Sensor wired to 5V (should be 3.3V)

### ❌ KY-039 stuck at 0/1023

* Finger placement wrong
* Too much light interference

### ❌ ThingSpeak not updating

* Interval < 15 seconds
* Wrong API key

### ❌ Blynk Compiler Error

Add required template defines at the TOP of code:

```cpp
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
```

---

# 📊 **System Workflow**

```
[ Sensors ]
   │
   ▼
NodeMCU ESP8266
   │
   ├──→ Real-Time App (Blynk)
   └──→ Cloud Storage (ThingSpeak)
```

---

# 📜 **License**

This project is open-source.
You may use it for **education, research, or personal use**.


