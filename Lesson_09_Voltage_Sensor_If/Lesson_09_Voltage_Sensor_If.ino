float R1 = 30000.0;
float R2 = 7500.0;
float battery_threshold = 7.8;

void setup() {
  pinMode(11, OUTPUT);

}

void loop() {
  int adc = analogRead(A0);
  float voltage = adc * 5 / 1024;
  float battery = voltage / (R2/(R1+R2));
  
  if(voltage < battery_threshold){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }

}
