
// Matrix L
float l1 = 9;
float l2 = 127;//127 
float l3 = 0.73;
float l4 = 0.065;
float lr = 0;
float x4old = 0; 
float yold = 0; 

// voltage limit 
float limit = 5;

float feedback(double y, long sampleFreq, double wheelAngle, double gyroDot){

  double sampleTime = (double) samplingTime; //(double) 1/sampleFreq;  
  float x4 = (float) wheelAngle; 
  float x3 = (x4-x4old)/(float) sampleTime;
  float x2 = (float) y;
  float x1 = (float) gyroDot; //(float) (y-yold)/ (float) sampleTime; //Testa gyrodot direkt (float) gyroDot; 

  x4old = x4; 
  yold = y; 
  
  float u = l1*x1 + l2*x2 + l3*x3 + l4*x4; 
  
  // saturation
  if(u < -limit)  
    u = -limit; 
  else if(u > limit) 
    u = limit; 
 // Serial.println(u); 
  return u; 

}
