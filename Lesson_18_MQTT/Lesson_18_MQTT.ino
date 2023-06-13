#include <WiFi.h>
#include <MQTT.h>
#include <SimpleDHT.h>

#define LED1    18
#define LED2    19
#define LED3    21
#define LED4    22
#define DHTPIN  23

const char ssid[] = "YourWiFiName";
const char password[] = "YourWiFiPassword";

WiFiClient net;
MQTTClient mqtt;

SimpleDHT11 dht11(DHTPIN);

unsigned long lastMillis = 0;

void wifiConnect() {
  Serial.print("Connecting to Wi-Fi '" + String(ssid) + "' ...");
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" connected.");

  mqtt.begin("mqtt.ariffinzulkifli.com", net);
  Serial.print("Connecting to MQTT broker ...");

  while (!mqtt.connect("YourESP32ClientID ")) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected.");

  mqtt.subscribe("YourESP32DeviceID/control/lamp1");
  mqtt.subscribe("YourESP32DeviceID/control/lamp2");
  mqtt.subscribe("YourESP32DeviceID/control/lamp3");
  mqtt.subscribe("YourESP32DeviceID/control/lamp4");
  mqtt.subscribe("YourESP32DeviceID/control/lampAll");
}

void messageReceived(String &topic, String &payload) {
  if(topic == "YourESP32DeviceID/control/lamp1"){
    digitalWrite(LED1, payload.toInt());
  }

  if(topic == "YourESP32DeviceID/control/lamp2"){
    digitalWrite(LED2, payload.toInt());
  }

  if(topic == "YourESP32DeviceID/control/lamp3"){
    digitalWrite(LED3, payload.toInt());
  }

  if(topic == "YourESP32DeviceID/control/lamp4"){
    digitalWrite(LED4, payload.toInt());
  }

  if(topic == "YourESP32DeviceID/control/lampAll"){
    digitalWrite(LED1, payload.toInt());
    digitalWrite(LED2, payload.toInt());
    digitalWrite(LED3, payload.toInt());
    digitalWrite(LED4, payload.toInt());

    if(payload.toInt() == 1){
      mqtt.publish("YourESP32DeviceID/control/lamp1", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp2", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp3", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp4", payload);
    }
    else{
      mqtt.publish("YourESP32DeviceID/control/lamp1", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp2", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp3", payload);
      mqtt.publish("YourESP32DeviceID/control/lamp4", payload);
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  wifiConnect();
  mqtt.onMessage(messageReceived);

}

void loop() {
  mqtt.loop();
  delay(10);  // <- fixes some issues with Wi-Fi stability

  if (!mqtt.connected()) {
    wifiConnect();
  }

  byte t, h;
  
  if ((dht11.read(&t, &h, NULL)) != SimpleDHTErrSuccess) {
    return;
  }

  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    
    mqtt.publish("YourESP32DeviceID/data/temperature", String(t));
    mqtt.publish("YourESP32DeviceID/data/humidity", String(h));
  }
}
