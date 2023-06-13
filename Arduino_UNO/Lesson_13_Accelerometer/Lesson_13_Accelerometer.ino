#include <Wire.h>

int ADXL345 = 0x53;

float X_out, Y_out, Z_out;

void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(ADXL345);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
  delay(10);
}

void loop() {
  
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32);
  Wire.endTransmission(false);
  
  Wire.requestFrom(ADXL345, 6, true);
  X_out = ( Wire.read()| Wire.read() << 8);
  X_out = X_out/256;
  Y_out = ( Wire.read()| Wire.read() << 8);
  Y_out = Y_out/256;
  Z_out = ( Wire.read()| Wire.read() << 8);
  Z_out = Z_out/256;

  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("   Ya= ");
  Serial.print(Y_out);
  Serial.print("   Za= ");
  Serial.println(Z_out);
  
  delay(500);
}
