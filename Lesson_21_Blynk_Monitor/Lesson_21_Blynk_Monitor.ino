#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN  "YOUR_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleDHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

int pinDHT11 = 23;
SimpleDHT11 dht11(pinDHT11);

unsigned long lastMillis = 0;

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

  byte temperature = 0;
  byte humidity = 0;
  
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    return;
  }
  
  Serial.print("Data OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" %RH");

  if(millis() - lastMillis > 15000){
    Blynk.virtualWrite(V2, temperature);
    Blynk.virtualWrite(V3, humidity);
  }
}
