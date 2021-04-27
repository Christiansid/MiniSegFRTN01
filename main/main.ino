#include <Wire.h>

#define samplingFreq 100
#define wheelEncoderPin1 2 
#define wheelEncoderPin2 3 

float r = 0; 

void setup(){
  setupWheel(); 
  Serial.begin(115200);
  IMUSetup();
  compFilterSetup();
  
}

void loop(){
  double alphaAccel = getAlphaAccel();
  double gyroDot = getGyroDot();
  double filteredSignal = compFilter(gyroDot, alphaAccel);
  double u = (double) feedback(filteredSignal, r, 1/samplingFreq);
  //Serial.println(filteredSignal);
  delay(1/samplingFreq);
  Serial.println(u);
  
}
