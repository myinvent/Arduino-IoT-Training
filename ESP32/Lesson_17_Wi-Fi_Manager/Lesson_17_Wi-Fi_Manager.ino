#include <WiFiManager.h>

#define ESP32_WIFI_SSID       "ESP32_Wi-Fi_SSID"
#define ESP32_WIFI_PASSWORD   "ESP32_Wi-Fi_Password"

void setup() {
    Serial.begin(115200);
    
    WiFiManager wm;

    bool res;
    res = wm.autoConnect(ESP32_WIFI_SSID, ESP32_WIFI_PASSWORD);

    if(!res) {
        Serial.println("Failed to connect!");
    } 
    else {
        Serial.println("ESP32 Wi-Fi Manager Ready.");
    }

}

void loop() {

}