#include <Ultrasonic.h>

Ultrasonic ultrasonic(2, 3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(1000);
}
