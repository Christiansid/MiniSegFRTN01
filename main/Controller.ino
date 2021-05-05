
// Matrix L
float l1 = 30.7241;
float l2 = 100.0955;
float l3 = 1.5702 ;
float l4 = 0.3162;
float lr = 0;
float x4old = 0; 
float yold = 0; 

// voltage limit 
float limit = 3.25;

float feedback(double y, long sampleFreq, double wheelAngle){

  double sampleTime = (double) 1/sampleFreq;  
  float x4 = wheelAngle; 
  float x3 = (x4-x4old)/sampleTime;
  float x2 = y;
  float x1 = (float) (y-yold)/ (float) sampleTime;
  x4old = x4; 
  yold = y; 
  
  float u = l1*x1 + l2*x2 + l3*x3 + l4*x4; 
  
  //Serial.println(u); 
  
//  Serial.print("x1: ");
//  Serial.print(x1);
//  Serial.print(" x2: ");
//  Serial.print(x2);
//  Serial.print(" x3: ");
//  Serial.print(x3);
//  Serial.print(" x4: ");
//  Serial.println(x4);


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
  
  return u; 

}
