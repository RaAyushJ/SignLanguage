#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* Gemini_Token = "GEMINI_API_KEY";
const char* Gemini_Max_Tokens = "100";

void setup() {
    SerialBT.begin("ESP32");
    Serial.begin(115200);

    // Connect to Wi-Fi network
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void loop() {
    String message = "";
    
    // Simulate sending a message when a specific character is received
    while (Serial.available() > 0) {
        char incomingChar = Serial.read();
        if (incomingChar == 's' || incomingChar == 'S') {
            Serial.println("Stopping the loop...");
            // You can handle stopping logic here if needed
            break;
        }
    }

    // Example: Sending a fixed message to Bluetooth
    message = "Hello from ESP32!";
    if (SerialBT.available()) {
        SerialBT.println(message);
    }

    // Simulating HTTP request
    HTTPClient https;
    if (https.begin("https://your-api-url.com?key=" + String(Gemini_Token))) {
        https.addHeader("Content-Type", "application/json");
        String payload = "{\"message\":\"" + message + "\"}";

        int httpCode = https.POST(payload);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String response = https.getString();
            Serial.println("Response: " + response);
            if (SerialBT.available()) {
                SerialBT.println(response);
            }
        } else {
            Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
        }
        https.end();
    } else {
        Serial.printf("[HTTPS] Unable to connect\n");
    }

    delay(1000); // Add some delay to avoid flooding
}
