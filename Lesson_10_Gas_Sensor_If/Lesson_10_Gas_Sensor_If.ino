float threshold = 2.5;

void setup() {
  pinMode(11, OUTPUT);

}

void loop() {
  int adc = analogRead(A0);
  float voltage = adc * 5 / 1024;
  
  if(voltage > threshold){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }

}
