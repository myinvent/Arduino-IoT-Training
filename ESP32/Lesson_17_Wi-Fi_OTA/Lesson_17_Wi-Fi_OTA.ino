#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

const char ssid[] = "YourWiFiName";
const char password[] = "YourWiFiPassword";

AsyncWebServer server(80);

unsigned long lastMillis = 0;
int ledPin = 16;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! I am ESP32.");
  });

  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();
  
  Serial.println("HTTP server started");
}

void loop() {
  if(millis() - lastMillis > 500){
    lastMillis = millis();

    ledState = not(ledState);
    digitalWrite(ledPin, ledState);
  }
}
