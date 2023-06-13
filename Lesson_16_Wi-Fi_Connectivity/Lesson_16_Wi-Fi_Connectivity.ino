#include <WiFi.h>

const char ssid[] = "YOUR_WIFI_NAME";
const char password[] = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s ", ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" CONNECTED.");

  Serial.print("ESP32 Station IP Address: ");
  Serial.println(WiFi.localIP().toString());

}

void loop() {

}
