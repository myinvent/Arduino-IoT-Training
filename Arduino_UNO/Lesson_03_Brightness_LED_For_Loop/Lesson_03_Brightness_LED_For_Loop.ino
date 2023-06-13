void setup() {
  pinMode(9, OUTPUT);

}

void loop() {

  for(int pwm = 0; pwm < 255; pwm++){
    analogWrite(9, pwm); delay(50);
  }

  for(int pwm = 255; pwm > 0; pwm--){
    analogWrite(9, pwm); delay(50);
  }
  
}