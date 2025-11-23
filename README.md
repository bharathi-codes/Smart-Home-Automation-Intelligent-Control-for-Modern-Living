# 🏠 Smart Home Automation – Intelligent Control for Modern Living

A complete **IoT-based Smart Home Automation System** built using **ESP32, Firebase, Web UI, Voice Commands, and IoT Sensors**.  
This system allows real-time control of home appliances like **lights, fans, and sensors** from anywhere using a **web dashboard** or **voice interface**.

This project was developed as part of the **Mini Project – B.Tech Information Technology (2025)**.

## 🔥 Features

### 🖥️ Dual Control System
- Web Dashboard (ON/OFF controls)
- Voice Commands (hands-free experience)
- Real-time control & status updates

### 📡 IoT Connectivity
- ESP32 microcontroller  
- DHT11 temperature sensor  
- Relay module  
- Firebase cloud sync  

### 🌐 Online + Offline Mode
- Cloud control  
- Local fallback mode  

### ⚙️ Automation Engine
- Event-based triggers  
- Scheduled routines  

### 🔐 Security & Monitoring
- Real-time alerts  
- Intrusion detection  
- Activity logs  

## 🏗️ System Architecture

User (Web / Voice) → Firebase / Local → ESP32 → Relays & Sensors

## 🧩 Modules
- Device Management  
- Automation Rules Engine  
- UI Module  
- Security & Monitoring  
- Connectivity Manager  

## 🔌 Hardware
ESP32, Relay, DHT11, LED/Bulb, Fan, Breadboard

## 💻 Software
Arduino IDE, Firebase, HTML/CSS/JS, Python

## 📜 ESP32 Sample Code

```cpp
String lightPath = "/devices/light_1/status";
if (Firebase.getString(firebaseData, lightPath)) {
  String cmd = firebaseData.stringData();
  digitalWrite(LED_PIN, cmd == "ON" ? HIGH : LOW);
}
```

## 📸 Screenshots
(Add images here)

## 🧠 Future Enhancements
- Google Home/Alexa integration  
- Mobile App  
- Energy analytics  

## 👨‍💻 Team
- Bharathi B  
- Kishore S  
- Mohamed Fazil H  
- Guide: Mr. S. Parthiban  

## 📜 License
Academic project. Free for learning use.
