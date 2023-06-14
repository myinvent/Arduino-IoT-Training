#include <WiFi.h>
#include <MQTT.h>
#include <SimpleDHT.h>

#define LED1    18
#define LED2    19
#define LED3    21
#define LED4    22
#define DHTPIN  23

#define WIFI_SSID             "Your_WiFi_SSID"
#define WIFI_PASSWORD         "Your_WiFi_Password"
#define MQTT_HOST             "MQTT_Broker_IP_or_DNS"
#define MQTT_PREFIX_TOPIC     "Your_Phone_Number/"
#define MQTT_PUBLISH_TOPIC    "monitor/"
#define MQTT_SUBSCRIBE_TOPIC  "control/"

WiFiClient net;
MQTTClient mqtt;

SimpleDHT11 dht11(DHTPIN);

unsigned long lastMillis = 0;

void connectToWiFiRouter() {
  Serial.print("Connecting to Wi-Fi '" + String(WIFI_SSID) + "' ...");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println(" connected!");
}

void mqttConnectToBroker(){
  Serial.print("Connecting to '" + String(WIFI_SSID) + "' ...");
  
  mqtt.begin(MQTT_HOST, net);
  mqtt.onMessage(mqttMessageReceived);

  String uniqueString = String(WIFI_SSID) + "-" + String(random(1, 98)) + String(random(99, 999));
  char uniqueClientID[uniqueString.length() + 1];
  
  uniqueString.toCharArray(uniqueClientID, uniqueString.length() + 1);
  
  while (!mqtt.connect(uniqueClientID)) {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");
  
  String SUBSCRIBE_TOPIC = String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC);

  mqtt.subscribe(SUBSCRIBE_TOPIC + "lamp1");
  mqtt.subscribe(SUBSCRIBE_TOPIC + "lamp2");
  mqtt.subscribe(SUBSCRIBE_TOPIC + "lamp3");
  mqtt.subscribe(SUBSCRIBE_TOPIC + "lamp4");
  mqtt.subscribe(SUBSCRIBE_TOPIC + "lampAll");
  
}

void mqttMessageReceived(String &topic, String &payload) {

  String SUBSCRIBE_TOPIC = String(MQTT_PREFIX_TOPIC) + String(MQTT_SUBSCRIBE_TOPIC);
  String device = topic.substring(topic.indexOf("control") + 8);

  if(device == "lamp1"){
    digitalWrite(LED1, payload.toInt());
  }
  else if(device == "lamp2"){
    digitalWrite(LED2, payload.toInt());
  }
  else if(device == "lamp3"){
    digitalWrite(LED3, payload.toInt());
  }
  else if(device == "lamp4"){
    digitalWrite(LED4, payload.toInt());
  }
  else if(device == "lampAll"){
    digitalWrite(LED1, payload.toInt());
    digitalWrite(LED2, payload.toInt());
    digitalWrite(LED3, payload.toInt());
    digitalWrite(LED4, payload.toInt());

    mqtt.publish(SUBSCRIBE_TOPIC + "lamp1", payload);
    mqtt.publish(SUBSCRIBE_TOPIC + "lamp2", payload);
    mqtt.publish(SUBSCRIBE_TOPIC + "lamp3", payload);
    mqtt.publish(SUBSCRIBE_TOPIC + "lamp4", payload);
  }
  else{

  }
}

void setup() {
  Serial.begin(9600);
  Serial.println();
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  connectToWiFiRouter();
  mqttConnectToBroker();

  Serial.println();

}

void loop() {
  mqtt.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFiRouter();
  }

  if (!mqtt.connected()) {
    mqttConnectToBroker();
  }

  byte temperature, humidity;
  
  if ((dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print(".");
    return;
  }
  Serial.println();

  Serial.println("Temperature: " + String(temperature) + " °C");
  Serial.println("Humidity: " + String(humidity) + " %RH");

  if (millis() - lastMillis > 10000) {
    lastMillis = millis();

    String PUBLISH_TOPIC = String(MQTT_PREFIX_TOPIC) + String(MQTT_PUBLISH_TOPIC);

    Serial.println("Publish Topic: " + PUBLISH_TOPIC + "temperature -> Value: " + String(temperature));
    Serial.println("Publish Topic: " + PUBLISH_TOPIC + "humidity -> Value: " + String(humidity));
    
    mqtt.publish(PUBLISH_TOPIC + "temperature", String(temperature));
    mqtt.publish(PUBLISH_TOPIC + "humidity", String(humidity));
  }
}
