#include <Wire.h>
#include <math.h>

#define samplingFreq 100

//Wheel encoder pins
#define wheelEncoderPin1 2
#define wheelEncoderPin2 3

void setup(){
  Serial.begin(115200);
  //IMUSetup();
  //compFilterSetup();
  setupWheel();
  
}

void loop(){
  //double alphaAccel = getAlphaAccel();
  //double gyroDot = getGyroDot();
  //double filteredSignal = compFilter(gyroDot, alphaAccel);
  //Serial.println(filteredSignal);
  //delay(1/samplingFreq);
  //Serial.println(getWheelRaw);
}
