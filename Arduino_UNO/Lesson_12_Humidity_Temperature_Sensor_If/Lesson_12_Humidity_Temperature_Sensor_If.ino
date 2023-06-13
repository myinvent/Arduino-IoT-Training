#include <SimpleDHT.h>

SimpleDHT11 dht11(3);

void setup() {
  pinMode(11, OUTPUT);
}

void loop() {
  byte t = 0;
  byte h = 0;
  
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(&t, &h, NULL)) != SimpleDHTErrSuccess) {
    return;
  }
  
  if(t > 30){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }

}
