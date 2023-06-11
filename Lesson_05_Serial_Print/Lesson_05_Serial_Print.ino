void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Hello ");
  Serial.println("awesome world!");
  delay(1000);
}
