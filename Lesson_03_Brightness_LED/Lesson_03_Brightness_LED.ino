void setup() {
  pinMode(9, OUTPUT);

}

void loop() {
  analogWrite(9, 10); delay(500);
  analogWrite(9, 20); delay(500);
  analogWrite(9, 30); delay(500);
  analogWrite(9, 40); delay(500);
  analogWrite(9, 50); delay(500);
  
}
