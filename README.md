# Health Monitoring System using IoT

[![NodeMCU](https://img.shields.io/badge/Platform-NodeMCU-blue.svg)](https://www.nodemcu.com/)
[![Arduino](https://img.shields.io/badge/IDE-Arduino-00979D.svg)](https://www.arduino.cc/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Dashboard](https://img.shields.io/badge/Dashboard-Live-success.svg)](https://mahesh-space.github.io/hms/)

> An IoT-based health monitoring system that tracks heart rate, blood oxygen saturation (SpO2), and body temperature in real-time using cloud platforms.

## 🌐 Live Dashboard

**[Medi-Guard Monitor - Real-time Patient Health Dashboard](https://mahesh-space.github.io/hms/)**

Experience our custom-built web dashboard featuring:
- 📊 Real-time health metrics visualization
- 🎨 Modern, responsive UI design
- 📱 Mobile-friendly interface
- 🔔 Alert notifications for abnormal readings
- 📈 Historical data charts
- 🎯 Patient-centric design

## 👥 Project Team

**Institution:** NIELIT AJMER
**Department:** B.Tech (Electronics & Communication / Computer Science)  
**Year:** 3rd Year  
**Academic Session:** 2025-2026

### Team Members:
- **Mahesh Gurjar** - Team Lead & Hardware Integration
- **Priyanshu Bharti** - Software Development & Cloud Integration
- **Priyanka Yadav** - Sensor Calibration & Testing
- **Shivraj Singh** - Documentation & IoT Platform Configuration

---

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Data Visualization](#data-visualization)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

---

## 🎯 Overview

This project implements a real-time health monitoring system using IoT technology. The system continuously monitors vital health parameters including heart rate, blood oxygen levels (SpO2), and body temperature. Data is transmitted to cloud platforms (ThingSpeak and Blynk) for remote monitoring, analysis, and visualization.

### Key Objectives:
- Develop a low-cost, portable health monitoring device
- Enable remote health monitoring through IoT platforms
- Provide real-time health data visualization
- Create an accessible healthcare solution for rural and remote areas

---

## ✨ Features

- ✅ **Real-time Heart Rate Monitoring** - Continuous BPM tracking using MAX30100 sensor
- ✅ **Blood Oxygen Saturation (SpO2)** - Measures oxygen levels in blood (%)
- ✅ **Body Temperature Monitoring** - Accurate temperature measurement with DS18B20
- ✅ **Cloud Integration** - Dual platform support (ThingSpeak & Blynk)
- ✅ **Custom Web Dashboard** - Professional UI with [Medi-Guard Monitor](https://mahesh-space.github.io/hms/)
- ✅ **WiFi Connectivity** - Wireless data transmission via NodeMCU ESP8266
- ✅ **Mobile App Support** - Monitor health data on smartphone via Blynk app
- ✅ **Visual Indicators** - LED feedback for heartbeat detection and data transmission
- ✅ **Serial Monitoring** - Real-time data display on Serial Monitor
- ✅ **Data Logging** - Historical data storage on ThingSpeak

---

## 🛠️ Hardware Requirements

| Component | Specification | Quantity | Purpose |
|-----------|---------------|----------|---------|
| NodeMCU ESP8266 | WiFi Module | 1 | Microcontroller & WiFi |
| MAX30100 | Pulse Oximeter | 1 | Heart Rate & SpO2 |
| DS18B20 | Digital Temperature Sensor | 1 | Body Temperature |
| Resistor | 4.7kΩ | 1 | Pull-up for DS18B20 |
| LED | 5mm (Red/Green) | 2 | Status Indicators |
| Resistor | 220Ω | 2 | LED Current Limiting |
| Breadboard | Standard | 1 | Circuit Assembly |
| Jumper Wires | Male-to-Male/Female | 20+ | Connections |
| USB Cable | Micro USB | 1 | Power & Programming |

### Optional Components:
- 3.7V Li-ion Battery (for portable operation)
- Battery Charging Module (TP4056)
- Enclosure/Case for final assembly

---

## 💻 Software Requirements

### Development Environment:
- **Arduino IDE** (v1.8.19 or higher)
- **USB Drivers** for NodeMCU CH340/CP2102

### Required Libraries:
```
1. ESP8266WiFi (Built-in)
2. BlynkSimpleEsp8266 (v1.0.1+)
3. MAX30100lib by OXullo Intersecans
4. OneWire by Paul Stoffregen (v2.3.7+)
5. DallasTemperature by Miles Burton (v3.9.0+)
6. Wire (Built-in for I2C)
```

### Cloud Platforms:
- **ThingSpeak** - Data logging and visualization
- **Blynk** - Mobile app monitoring and control
- **Medi-Guard Monitor** - Custom web dashboard ([Live Demo](https://mahesh-space.github.io/hms/))

---

## 🔌 Circuit Diagram

### Pin Connections:

**MAX30100 (Pulse Oximeter & SpO2 Sensor):**
```
MAX30100    →    NodeMCU
   VCC      →    3.3V ⚠️ (NOT 5V!)
   GND      →    GND
   SDA      →    D2 (GPIO4)
   SCL      →    D1 (GPIO5)
```

**DS18B20 (Temperature Sensor):**
```
DS18B20     →    NodeMCU
   VCC      →    3.3V
   GND      →    GND
   DATA     →    D3 (GPIO0)
   
Note: Connect 4.7kΩ resistor between DATA and VCC
```

**Status LEDs (Optional):**
```
Component        →    NodeMCU
LED1 (Heartbeat) →    D6 → 220Ω → LED → GND
LED2 (TX Data)   →    D7 → 220Ω → LED → GND
```

### Circuit Schematic:
```
                     NodeMCU ESP8266
                    ┌─────────────┐
                    │             │
       MAX30100     │   D1 (SCL)  ├──┐
          ┌─────────┤   D2 (SDA)  ├──┤
          │         │   D3        ├────── DS18B20 (+ 4.7kΩ pullup)
          │         │   D6        ├────── LED (Heartbeat)
          │         │   D7        ├────── LED (TX)
          │         │   3.3V      ├────── VCC (All sensors)
          │         │   GND       ├────── GND (Common)
          │         └─────────────┘
          │
      I2C Bus
```

---

## 📥 Installation

### Step 1: Arduino IDE Setup
1. Download and install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP8266 Board Manager URL:
   - Go to `File` → `Preferences`
   - Add to "Additional Board Manager URLs":
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
3. Install ESP8266 Board:
   - Go to `Tools` → `Board` → `Boards Manager`
   - Search "ESP8266" and install

### Step 2: Install Libraries
Open Arduino IDE → `Sketch` → `Include Library` → `Manage Libraries`

Install the following:
- **Blynk** (by Volodymyr Shymanskyy)
- **MAX30100lib** (by OXullo Intersecans)
- **OneWire** (by Paul Stoffregen)
- **DallasTemperature** (by Miles Burton)

### Step 3: Download Project Code
```bash
git clone https://github.com/yourusername/health-monitoring-iot.git
cd health-monitoring-iot
```

Or download the `.ino` file directly from the repository.

---

## ⚙️ Configuration

### 1. ThingSpeak Setup

1. Create account at [ThingSpeak.com](https://thingspeak.com/)
2. Create a new channel with 3 fields:
   - **Field 1:** Heart Rate (BPM)
   - **Field 2:** SpO2 (%)
   - **Field 3:** Body Temperature (°C)
3. Copy your **Write API Key**
4. Update in code:
```cpp
String apiKey = "YOUR_THINGSPEAK_API_KEY";
```

### 2. Blynk Setup

1. Download **Blynk App** (iOS/Android)
2. Create new project → Select "NodeMCU" device
3. Create a template and get credentials:
   - `BLYNK_TEMPLATE_ID`
   - `BLYNK_TEMPLATE_NAME`
   - `BLYNK_AUTH_TOKEN`
4. Add widgets:
   - **Value Display (V1)** → Heart Rate
   - **Value Display (V2)** → SpO2
   - **Value Display (V3)** → Body Temperature
5. Update credentials in code:
```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
```

### 3. WiFi Configuration

Update your WiFi credentials:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

## 🚀 Usage

### Uploading Code:
1. Connect NodeMCU to computer via USB
2. Select board: `Tools` → `Board` → `NodeMCU 1.0 (ESP-12E Module)`
3. Select port: `Tools` → `Port` → (Your COM port)
4. Set upload speed: `115200`
5. Click **Upload** button

### Operating the System:
1. Power on the NodeMCU
2. Wait for WiFi connection (LED indicators will show status)
3. Place your finger gently on MAX30100 sensor
4. Keep finger still for 10-15 seconds for stable readings
5. View real-time data on:
   - Serial Monitor (115200 baud)
   - Blynk mobile app
   - ThingSpeak dashboard

### Reading Data:

**Serial Monitor Output:**
```
=================================
Health Monitoring System Starting
=================================
Initializing MAX30100...SUCCESS!
Initializing DS18B20...SUCCESS!
Found 1 temperature sensor(s)

Connecting to WiFi: YourWiFi
WiFi connected!
IP address: 192.168.1.100

System Ready!
=================================

💓 Beat!
--- Sensor Readings ---
Heart Rate: 75.2 bpm  |  SpO2: 98 %  |  Body Temp: 36.8 °C

✓ Data sent to ThingSpeak!
========================
```

---

## 📊 Data Visualization

### Medi-Guard Monitor Dashboard (Primary):
**🌐 [Live Dashboard](https://mahesh-space.github.io/hms/)**

Our custom-built web interface provides:
- **Real-time Monitoring**: Live health metrics with smooth animations
- **Patient Information**: Display patient details and status
- **Visual Indicators**: Color-coded alerts for abnormal readings
- **Responsive Design**: Works seamlessly on desktop, tablet, and mobile
- **Modern UI/UX**: Intuitive interface with glassmorphism design
- **Data Visualization**: Interactive charts and graphs
- **Alert System**: Visual and audio notifications for critical values
- **Multi-parameter Display**: All vitals in one comprehensive view

**Normal Ranges Displayed:**
- Heart Rate: 60-100 BPM
- SpO2: 95-100%
- Body Temperature: 36.1-37.2°C

### ThingSpeak Dashboard:
- Access your channel at: `https://thingspeak.com/channels/YOUR_CHANNEL_ID`
- View real-time graphs for all three parameters
- Export data in CSV/JSON format
- Set up MATLAB analysis for advanced processing
- Configure alerts for abnormal readings

### Blynk Mobile App:
- Real-time value displays
- Historical data charts
- Custom notifications
- Widget customization
- Remote monitoring from anywhere

---

## 🔧 Troubleshooting

### Issue: MAX30100 not detected
**Solution:**
- Check I2C connections (SDA, SCL)
- Ensure sensor is powered with 3.3V (NOT 5V)
- Try different I2C pins if needed
- Test with I2C scanner sketch

### Issue: Invalid temperature readings
**Solution:**
- Verify 4.7kΩ pull-up resistor is connected
- Check DS18B20 wiring
- Ensure good contact with sensor
- Try different GPIO pin

### Issue: WiFi not connecting
**Solution:**
- Check SSID and password
- Ensure 2.4GHz WiFi (ESP8266 doesn't support 5GHz)
- Move closer to router
- Check router settings (firewall, MAC filtering)

### Issue: No heart rate detected
**Solution:**
- Place finger gently (don't press too hard)
- Keep finger completely still
- Clean sensor surface
- Avoid bright light on sensor
- Wait 10-15 seconds for calibration

### Issue: Blynk connection failed
**Solution:**
- Verify auth token is correct
- Check template ID and name
- Ensure virtual pins match (V1, V2, V3)
- Update Blynk library to latest version

---

## 🔮 Future Enhancements

### Planned Features:
- [x] Custom web dashboard (Medi-Guard Monitor)
- [ ] ECG monitoring capability
- [ ] GPS location tracking
- [ ] Emergency alert system (SMS/Email)
- [ ] Machine learning for anomaly detection
- [ ] Multi-user support with patient profiles
- [ ] Historical data analysis dashboard
- [ ] Voice alerts using speaker module
- [ ] Battery level monitoring
- [ ] Sleep mode for power saving
- [ ] OLED display for offline viewing
- [ ] Integration with smartwatches
- [ ] Telemedicine consultation feature
- [ ] Doctor appointment scheduling
- [ ] PDF report generation

### Hardware Upgrades:
- [ ] PCB design for compact assembly
- [ ] 3D printed enclosure
- [ ] Rechargeable battery pack
- [ ] Solar charging option
- [ ] Wearable form factor

---

## 🤝 Contributing

We welcome contributions to improve this project! Here's how you can help:

1. **Fork** the repository
2. **Create** a new branch (`git checkout -b feature/improvement`)
3. **Make** your changes
4. **Test** thoroughly
5. **Commit** your changes (`git commit -am 'Add new feature'`)
6. **Push** to branch (`git push origin feature/improvement`)
7. **Create** a Pull Request

### Areas for Contribution:
- Code optimization
- Bug fixes
- Documentation improvements
- New sensor integration
- UI/UX enhancements
- Testing and validation

---

## 📝 Project Report

### Abstract:
This project demonstrates the implementation of an IoT-based health monitoring system using NodeMCU ESP8266, MAX30100 pulse oximeter, and DS18B20 temperature sensor. The system continuously monitors vital health parameters and transmits data to cloud platforms for remote monitoring and analysis.

### Applications:
- Home health monitoring
- Remote patient monitoring
- Elderly care facilities
- Sports and fitness tracking
- Post-operative care
- Quarantine monitoring
- Rural healthcare access

### Learning Outcomes:
1. Understanding IoT architecture and protocols
2. Sensor interfacing and calibration
3. Cloud platform integration
4. Real-time data processing
5. WiFi communication with ESP8266
6. Mobile app development with Blynk
7. Hardware-software integration

---

## 📚 References

1. MAX30100 Datasheet - Maxim Integrated
2. DS18B20 Technical Documentation - Dallas Semiconductor
3. ESP8266 Technical Reference - Espressif Systems
4. ThingSpeak Documentation - MathWorks
5. Blynk Platform Guide - Blynk Inc.
6. Arduino Programming Reference
7. IoT Healthcare Research Papers

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 📧 Contact

For questions, suggestions, or collaboration:

- **Mahesh Gurjar** - Project Lead  
  Email: mahesh.gurjar@college.edu

- **Priyanshu Bharti** - Software Developer  
  Email: priyanshu.bharti@college.edu

- **Priyanka Yadav** - Hardware Engineer  
  Email: priyanka.yadav@college.edu

- **Shivraj Singh** - Documentation Lead  
  Email: shivraj.singh@college.edu

**Project Repository:** [GitHub Link]  
**Live Dashboard:** https://mahesh-space.github.io/hms/  
**Project Documentation:** [Documentation Link]

---

## 🙏 Acknowledgments

We would like to thank:
- Our project guide **[Guide Name]** for valuable guidance
- Department of [Your Department] for lab facilities
- [College Name] for project support
- Open-source community for libraries and tools
- All contributors and testers

---

## 📊 Project Statistics

- **Development Time:** 3 months
- **Total Code Lines:** ~350 lines (Arduino) + Custom Web Dashboard
- **Sensors Used:** 2
- **Cloud Platforms:** 2 + Custom Dashboard
- **Dashboards:** 3 (ThingSpeak, Blynk, Medi-Guard Monitor)
- **Accuracy:** ±2% (SpO2), ±0.5°C (Temperature), ±3 BPM (Heart Rate)
- **Update Frequency:** Real-time (1 sec), Cloud (15 sec)
- **Power Consumption:** ~150mA average
- **Cost:** ≈ ₹2000-2500 (~$25-30 USD)
- **Web Technologies:** HTML5, CSS3, JavaScript

---

<div align="center">

### 🌟 [Visit Our Live Dashboard](https://mahesh-space.github.io/hms/) 🌟

**Made with ❤️ by 3rd Year B.Tech Students**

⭐ Star this repository if you found it helpful!

</div>

---

**Last Updated:** December 2025  
**Version:** 1.0.0  
**Status:** ✅ Active Development
