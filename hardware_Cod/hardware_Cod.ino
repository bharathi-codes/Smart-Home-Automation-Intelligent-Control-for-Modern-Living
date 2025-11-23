#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <EEPROM.h>

// ====== WiFi Configuration ======
const char* ssid = "Smart_Home_Automation";     // Hotspot name (you can change)
const char* password = "12345678";        // Hotspot password

// ====== DHT Configuration ======
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ====== Motor Configuration ======
#define MOTOR_PIN 13  // controls transistor/relay
#define EEPROM_SIZE 1 // to store motor state

// ====== Global Variables ======
WebServer server(80);
bool motorState = false;

// ====== Functions ======
void saveMotorState(bool state) {
  EEPROM.write(0, state);
  EEPROM.commit();
}

bool loadMotorState() {
  return EEPROM.read(0);
}

String getWebPage(float temp, float hum) {
  String state = motorState ? "ON" : "OFF";
  String btnLabel = motorState ? "Turn ON" : "Turn OFF";
  String btnClass = motorState ? "off" : "on";

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>Smart Home Automation</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
      body { font-family: Arial; background: #0b132b; color: white; text-align: center; padding: 30px; }
      h1 { color: #00d1ff; }
      button { padding: 12px 24px; margin: 10px; font-size: 16px; border: none; border-radius: 8px; cursor: pointer; }
      .on { background: #00ff88; color: black; }
      .off { background: #ff0044; color: white; }
      #voice { background: #444; color: white; }
      .data { margin-top: 20px; font-size: 18px; }
    </style>
  </head>
  <body>
    <h1>Smart Home Automation</h1>
    <p>Motor State: <b id="motorState">)rawliteral" + state + R"rawliteral(</b></p>
    <button id="toggleBtn" class=")rawliteral" + btnClass + R"rawliteral(" onclick="toggleMotor()">)rawliteral" + btnLabel + R"rawliteral(</button>
    
    <div class="data">
      <p>Temperature: <b id="temp">)rawliteral" + String(temp) + R"rawliteral(°C</b></p>
      <p>Humidity: <b id="hum">)rawliteral" + String(hum) + R"rawliteral(%</b></p>
    </div>
    
    <button id="voice" onclick="startVoice()">🎤 Voice Command</button>

    <script>
      function toggleMotor() {
        fetch('/toggle').then(res => res.text()).then(data => {
          document.getElementById('motorState').innerText = data;
          location.reload();
        });
      }

      setInterval(() => {
        fetch('/data').then(res => res.json()).then(data => {
          document.getElementById('temp').innerText = data.temp + "°C";
          document.getElementById('hum').innerText = data.hum + "%";
        });
      }, 2000);

      function startVoice() {
        const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
        const recognition = new SpeechRecognition();
        recognition.lang = 'en-IN';
        recognition.start();
        recognition.onresult = (event) => {
          const command = event.results[0][0].transcript.toLowerCase();
          if (command.includes('on')) fetch('/on');
          else if (command.includes('off')) fetch('/off');
        };
      }
    </script>
  </body>
  </html>
  )rawliteral";

  return html;
}

// ====== Route Handlers ======
void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  server.send(200, "text/html", getWebPage(temp, hum));
}

void handleToggle() {
  motorState = !motorState;
  digitalWrite(MOTOR_PIN, motorState ? HIGH : LOW);
  saveMotorState(motorState);
  server.send(200, "text/plain", motorState ? "ON" : "OFF");
}

void handleOn() {
  motorState = true;
  digitalWrite(MOTOR_PIN, HIGH);
  saveMotorState(motorState);
  server.send(200, "text/plain", "Motor ON");
}

void handleOff() {
  motorState = false;
  digitalWrite(MOTOR_PIN, LOW);
  saveMotorState(motorState);
  server.send(200, "text/plain", "Motor OFF");
}

void handleData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String json = "{\"temp\":" + String(temp) + ",\"hum\":" + String(hum) + "}";
  server.send(200, "application/json", json);
}

// ====== Setup ======
void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  dht.begin();

  // Load last saved motor state
  motorState = loadMotorState();
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, motorState ? HIGH : LOW);

  // Start WiFi in Access Point mode
  WiFi.softAP(ssid, password);
  Serial.println("WiFi started!");
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  // Route setup
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/data", handleData);

  server.begin();
  Serial.println("Server started!");
}

// ====== Loop ======
void loop() {
  server.handleClient();
}
