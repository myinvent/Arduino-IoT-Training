#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";


BLYNK_WRITE(V0) {
  int value = param.asInt();

  pinMode(18, OUTPUT);
  digitalWrite(18, value);
}


BLYNK_WRITE(V1) {
  int value = param.asInt();

  pinMode(19, OUTPUT);
  digitalWrite(19, value);
}


void setup() {
  Serial.begin(9600);
  while(!Serial);

  Blynk.begin(auth, ssid, pass);
}


void loop() {
  Blynk.run();
}
