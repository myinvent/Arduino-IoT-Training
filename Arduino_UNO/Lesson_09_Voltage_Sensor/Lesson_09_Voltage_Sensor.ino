float R1 = 30000.0;
float R2 = 7500.0;

void setup() {
  Serial.begin(9600);
  pinMode(11, OUTPUT);

}

void loop() {
  int adc = analogRead(A0);
  float voltage = adc * 5 / 1024;
  float battery = voltage / (R2/(R1+R2));
  
  Serial.println(battery);
  
  delay(500);

}
