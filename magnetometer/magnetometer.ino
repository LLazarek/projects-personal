
// Code adapted from
// "Wire Master Reader/Writer" by Nicholas Zambetti <http://www.zambetti.com>


#include <Wire.h>

byte readings[6] = {0};

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.beginTransmission(0x3C); // Write data to magnetometer
  //Wire.write(0x3C);
  Wire.write(0x03); // Set register pointer to X MSB
  Wire.requestFrom(0x3D, 6);    // request 6 bytes (X1, X2, Y1, Y2, Z1, Z2)
  while(!Wire.available()){
    Serial.println("Waiting...");
    delay(100);
  }
  for(int i = 0; i < 6 && Wire.available(); ++i) { // slave may send less than requested
    readings[i] = Wire.read(); // receive a byte as character
    Serial.println(readings[i]);         // print the character
  }
  int x = readings[0];
  x <<= 8;
  x |= readings[1];

  int y = readings[2];
  y <<= 8;
  y |= readings[3];

  int z = readings[4];
  z <<= 8;
  z |= readings[5];

  Serial.print("X = "), Serial.println(x);
  Serial.print("Y = "), Serial.println(y);
  Serial.print("Z = "), Serial.println(z);

  delay(10000);
}
