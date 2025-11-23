🏠 Smart Home Automation – Intelligent Control for Modern Living

A fully functional IoT-based Smart Home Automation System that allows users to control lights, fans, and sensors through a web interface and voice commands.
Designed as a mini-project for the 2025 B.Tech IT (5th Semester), this system combines hardware + cloud + web technologies to modernize how home appliances are controlled.

🚀 Features
✅ 1. Dual Control System

Web Interface: Switch appliances ON/OFF remotely

Voice Control: Execute commands hands-free

Centralized Dashboard: All devices visible in one place

✅ 2. Real-Time IoT Integration

ESP32 microcontroller

DHT11 temperature sensor

Relay module for appliance switching

Live sensor updates via Firebase

✅ 3. Online + Offline Mode (Dual Connectivity)

Cloud Mode: Control from anywhere using Firebase

Local Mode: Works even without internet

✅ 4. Automation & Intelligence

Automation rule engine

Scheduled routines (e.g., turn on light at 6 PM)

Room-based device grouping

Energy usage monitoring

✅ 5. Security & User Management

Secure login

Real-time monitoring

Alerts for unusual activity

Multi-user access support

🧱 System Architecture

The project is built around a central IoT hub (ESP32) that communicates with the cloud and UI.

User (Web / Voice)
        |
        v
Firebase Cloud / Local Network
        |
        v
Control Hub (ESP32)
        |
        v
Appliances (Lights, Fans, Sensors)

📦 Module Breakdown
🔌 Device Management Module

Registers and manages all connected smart devices

Tracks device states (ON/OFF, sensor data)

Handles communication between ESP32 and cloud

💡 Automation Rules Engine

Executes “If–This–Then–That” logic

Supports custom schedules

Turns sensor inputs into automated actions

🕹️ User Interface Module

Web dashboard with device cards

Real-time updates

Voice command interface

🔐 Security & Monitoring

Detects hazards or intrusions

Sends alerts to the user

Maintains history logs

🌐 Connectivity Manager

Switches automatically between local mode & cloud mode

Manages communication reliability

🛠️ Tech Stack
💻 Software

Python (for dashboard / backend components)

Arduino IDE (for ESP32 firmware)

Firebase (Realtime Database)

HTML/CSS/JS (web interface)

🔧 Hardware

ESP32 Microcontroller

DHT11 Sensor

Relay Module

LED / Bulb

Fan Motor

Breadboard + jumper wires

🔌 ESP32 Firmware Snippet

Example command-reading logic:

String lightPath = "/devices/light_1/status";

if (Firebase.getString(firebaseData, lightPath)) {
  String command = firebaseData.stringData();
  
  if (command == "ON") {
    digitalWrite(LED_PIN, HIGH);
  } else if (command == "OFF") {
    digitalWrite(LED_PIN, LOW);
  }
}


Temperature sync to cloud:

float temperature = dht.readTemperature();
Firebase.setFloat(firebaseData, "/sensors/temperature", temperature);

📊 Results
✔ Secure Login

Simple login page for authentication.

✔ Device Dashboard

Shows all devices

Toggle switches

Room-based navigation

✔ Real-Time Sensor Readings

Temperature updates

Cloud sync every 5 seconds

✔ Voice Control

Execute commands like:

"Turn on light"

"Turn off fan"

🎯 Conclusion

This Smart Home Automation system provides a modern, reliable, and user-friendly solution for managing appliances.
With dual-mode functionality, intuitive control methods, and IoT intelligence, it brings traditional homes one step closer to smart living.

🔮 Future Enhancements

Deep learning for voice processing

Predictive energy optimization

Integration with Google Home / Alexa

Mobile app (Flutter/React Native)

👤 Team Members

Bharathi B

Kishore S

Mohamed Fazil H

Guide: Mr. S. Parthiban, AP/IT
