void setup() {
  pinMode(11, OUTPUT);
  pinMode(7, INPUT);

}

void loop() {
  int buttonStatus = digitalRead(7);

  if(buttonStatus == 1){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }

}