void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()){
    String data = Serial.readString();
    Serial.println(data);

    if(data == "hello world"){
      Serial.println("Correct");
    }
    else{
      Serial.println("Incorrect");
    }
  }
}
