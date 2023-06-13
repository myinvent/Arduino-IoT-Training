#include <WiFi.h>
#include <MQTT.h>
#include <SimpleDHT.h>

#define LED1    18
#define LED2    19
#define LED3    21
#define LED4    22
#define DHTPIN  23

const char ssid[] = "YOUR_WIFI_SSID";
const char password[] = "YOUR_WIFI_PASSWORD";
const char deviceDeveloperId[] = "YOUR_DEVICE_DEVELOPER_ID";
const char deviceAccessToken[] = "YOUR_DEVICE_ACCESS_TOKEN";
const char publishTopic[] = "/v2/streams";
const char statusTopic[] = "/v2/streams/status";

WiFiClient net;
MQTTClient mqtt(1024);

SimpleDHT11 dht11(DHTPIN);

unsigned long lastMillis = 0;

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi '" + String(ssid) + "' ...");

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" connected!");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming Status: " + payload);
  Serial.println();
}

void connectToFavoriotMQTT(){
  Serial.print("Connecting to Favoriot MQTT ...");
  
  mqtt.begin("mqtt.favoriot.com", net);
  mqtt.onMessage(messageReceived);

  String uniqueString = String(ssid) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];
  
  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);
  
  while (!mqtt.connect(uniqueClientID, deviceAccessToken, deviceAccessToken)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");

  Serial.println("Subscribe to: " + String(deviceAccessToken) + String(statusTopic));
  
  mqtt.subscribe(String(deviceAccessToken) + String(statusTopic));
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
 
  connectToWiFi();
  connectToFavoriotMQTT();
}

void loop() {
  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }

  if (!mqtt.connected()) {
    connectToFavoriotMQTT();
  }

  byte t, h;
  
  if ((dht11.read(&t, &h, NULL)) != SimpleDHTErrSuccess) {
    return;
  }

  // publish a message roughly every 10 seconds.
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    String favoriotJson = "{";
    favoriotJson += "\"device_developer_id\":\"" + String(deviceDeveloperId) + "\",";
    favoriotJson += "\"data\":{";
    favoriotJson += "\"temperature\":" + String(t) + ",";
    favoriotJson += "\"humidity\":" + String(h);
    favoriotJson += "}";
    favoriotJson += "}";

    Serial.println("Temperature: " + String(t) + " °C");
    Serial.println("Humidity: " + String(h) + " %RH");

    Serial.println("Data to Publish: " + favoriotJson);
    Serial.println("Publish to: " + String(deviceAccessToken) + String(publishTopic));
    
    mqtt.publish(String(deviceAccessToken) + String(publishTopic), favoriotJson);
    
  }
}
