void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);

}

void loop() {
  int adc = analogRead(A0);
  float voltage = adc * 5 / 1024;
  
  Serial.println(voltage);
  
  delay(500);

}
