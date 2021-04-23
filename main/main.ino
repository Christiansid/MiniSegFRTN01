#include <Wire.h>

#define samplingFreq 100

void setup(){
  Serial.begin(115200);
  IMUSetup();
}

void loop(){
  readAccel();
  delay(10);
}
