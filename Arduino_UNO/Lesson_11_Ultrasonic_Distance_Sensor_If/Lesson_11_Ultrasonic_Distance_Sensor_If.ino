#include <Ultrasonic.h>

Ultrasonic ultrasonic(2, 3);

void setup() {
  pinMode(11, OUTPUT);
}

void loop() {
  int distance = ultrasonic.read();

  if(distance < 10){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }

  delay(1000);

}
