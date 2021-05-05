#include <Wire.h>
#include <math.h>

#include <MPU6050.h>
#include <SoftwareSerial.h>

#define samplingFreq 50
#define wheelEncoderPin1 2 
#define wheelEncoderPin2 3 
#define motorPinF 5
#define motorPinB 4

SoftwareSerial hc06(1,0);

//Wheel encoder pins
#define wheelEncoderPin1 2
#define wheelEncoderPin2 3

void setup(){
  Serial.begin(115200);
  IMUSetup();
  compFilterSetup();
  setupWheel();
  
}

void loop(){
  double alphaAccel = getAlphaAccel();
  double gyroDot = getGyroDot();
  double wheelAngle = getWheelAngle();
  double filteredSignal = compFilter(gyroDot, alphaAccel);
  double u = (double) feedback(filteredSignal, samplingFreq, wheelAngle);
  //Serial.println(filteredSignal);
  delay(1000/samplingFreq);
  //Serial.println(u);
  if(u > 0){
    forward(u);
  } else if(u < 0){
    backward(-1*u);
  };
  
}

void forward(int speed){
  digitalWrite(motorPinB, LOW);
  analogWrite(motorPinF, speed * 78); 
}

void backward(int speed){
  digitalWrite(motorPinF, LOW);
  analogWrite(motorPinB, speed * 78);
}
