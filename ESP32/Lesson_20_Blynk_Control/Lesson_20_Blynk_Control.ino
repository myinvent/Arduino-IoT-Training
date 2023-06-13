#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define LED1    18
#define LED2    19
#define LED3    21
#define LED4    22

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

BLYNK_WRITE(V0) {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, param.asInt());
}

BLYNK_WRITE(V1) {
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, param.asInt());
}

BLYNK_WRITE(V2) {
  pinMode(LED3, OUTPUT);
  digitalWrite(LED3, param.asInt());
}

BLYNK_WRITE(V3) {
  pinMode(LED4, OUTPUT);
  digitalWrite(LED4, param.asInt());
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
