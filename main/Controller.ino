
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
 // Serial.print(x1*l1);
 // Serial.print("\t");
//  Serial.println(x2);
  x4old = x4; 
  yold = y; 
  
  float u = l1*x1 + l2*x2 + l3*x3 + l4*x4; 
  

  
 // Serial.print("x1: ");
  //Serial.print(x1*l1);
  //Serial.print("\t");
  //Serial.print("x2: ");
 // Serial.print(x2*l2);
  //Serial.print("\t");
 // Serial.print("x3: ");
  //Serial.print(x3*l3);
  //Serial.print("\t");
//  Serial.print("x4: ");
  //Serial.println(x4*l4);


 // x1prim = a11*x1+a12*x2+a13*x3+a14*x4+b1*u;           
 // x2prim = a21*x1+a22*x2+a23*x3+a24*x4+b2*u;
 // x3prim = a31*x1+a32*x2+a33*x3+a34*x4+b3*u;
 // x4prim = a41*x1+a42*x2+a43*x3+a44*x4+b4*u;  

//  Serial.print("x1Prim: ");
//  Serial.print(x1prim);
//  Serial.print(" x2Prim: ");
//  Serial.print(x2prim);
//  Serial.print(" x3Prim: ");
//  Serial.print(x3prim);
//  Serial.print(" x4Prim: ");
//  Serial.println(x4prim);


  // saturation
  if(u < -limit)  
    u = -limit; 
  else if(u > limit) 
    u = limit; 
 // Serial.println(u); 
  return u; 

}
