#include <Wire.h>

#define samplingFreq 100

void setup(){
  Serial.begin(115200);
  IMUSetup();
  compFilterSetup();
  
}

void loop(){
  double alphaAccel = getAlphaAccel();
  double gyroDot = getGyroDot();
  double filteredSignal = compFilter(gyroDot, alphaAccel);
  Serial.println(filteredSignal);
  delay(1/samplingFreq);
}
