#include <SimpleDHT.h>

SimpleDHT11 dht11(3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  byte t = 0;
  byte h = 0;
  
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(&t, &h, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(",");
    Serial.println(SimpleDHTErrDuration(err));
    
    delay(1000);
    
    return;
  }
  
  Serial.print("Sample OK: ");
  
  Serial.print((int)t);
  Serial.print(" *C, ");
  
  Serial.print((int)h);
  Serial.println(" %RH");
  
  delay(1500);
}
