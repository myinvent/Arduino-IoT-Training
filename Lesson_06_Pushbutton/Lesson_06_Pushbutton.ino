void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);

}

void loop() {
  int buttonStatus = digitalRead(7);

  Serial.println(buttonStatus);

  delay(500);

}