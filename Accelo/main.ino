#include <Wire.h>

void setup(){
  Serial.begin(115200);
  AcceloSetup();
}

void loop(){
  readAccel();
  delay(10);
}
