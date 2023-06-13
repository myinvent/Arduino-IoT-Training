void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  kelip(9, 100);
  kelip(10, 1000);
  kelip(11, 500);
  kelip(12, 700);
}

void kelip(int pin, int masa){
  digitalWrite(pin, HIGH);
  delay(masa);
  digitalWrite(pin, LOW);
  delay(masa);
}