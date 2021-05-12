#include <Wire.h>
#include <math.h>

#include <MPU6050.h>

#define samplingTime 0.020
#define wheelEncoderPin1 2 
#define wheelEncoderPin2 3 
#define motorPinF 5
#define motorPinB 4
long now; 
long printIDX = 0;


//Wheel encoder pins
#define wheelEncoderPin1 2
#define wheelEncoderPin2 3

void setup(){
  Serial.begin(115200);
  IMUSetup();
  compFilterSetup();
  pinMode(motorPinF, OUTPUT);
  pinMode(motorPinB, OUTPUT);  
  setupWheel();
  
}

void loop(){
 
  double wheelAngle = getWheelAngle(); 
  double alphaAccel = (double) getAlphaAccel();
  double gyroDot = (double) getGyroDot();
  double filteredSignal = compFilter(gyroDot, alphaAccel);
  double u = (double) feedback(filteredSignal, samplingTime, wheelAngle, gyroDot);
  delay(samplingTime*1000);//delay(1000/samplingFreq);
  

  Serial.print(wheelAngle);
  Serial.print("\t");
  Serial.print(filteredSignal*100);
  Serial.print("\t");
  Serial.println(u);
  if(u >= 0){
    forward(u);
  } else if(u < 0){
    backward(-1*u);
  }; 
}

void forward(int speed){
  digitalWrite(motorPinB, LOW);
  analogWrite(motorPinF, speed * 51); 
}

void backward(int speed){
  digitalWrite(motorPinF, LOW);
  analogWrite(motorPinB, speed *51);
}
