#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleDHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

#define LED1    18
#define LED2    19
#define LED3    21
#define LED4    22
#define DHTPIN  23

SimpleDHT11 dht11(DHTPIN);

unsigned long lastMillis = 0;

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

  byte temperature = 0;
  byte humidity = 0;
  
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print(".");
    return;
  }
  Serial.println();
  
  Serial.println("Temperature: " + String(temperature) + " °C");
  Serial.println("Humidity: " + String(humidity) + " %RH");

  if(millis() - lastMillis > 15000){
    Serial.println("=> Send data to Blynk App.");

    Blynk.virtualWrite(V4, temperature);
    Blynk.virtualWrite(V5, humidity);
  }
}
