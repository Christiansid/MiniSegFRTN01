
  
// Matrix A
float a11 = 3.1; 
float a12 = 58.4; 
float a13 = 62.7; 
float a14 = 0;
float a21 = 1; 
float a22 = 0; 
float a23 = 0; 
float a24 = 0; 
float a31 = 40.1; 
float a32 = -318;
float a33 = -766; 
float a34 = 0; 
float a41 = 0; 
float a42 = 0; 
float a43 = 1; 
float a44 = 0; 

// Matrix B
float b1 = -148; 
float b2 = 0; 
float b3 = 1808; 
float b4 = 0; 

// Matrix L
float l1 = 50.2010;
float l2 = 170.8322;
float l3 = 2.7471;
float l4 = 2.4332;
float lr = 0;

// voltage limit 
float limit = 3.25;
float x1prim = 0 ;
float x2prim = 0 ;
float x3prim = 0 ;
float x4prim = 0 ;
float x2old ;
float yold;


float feedback(double y, float r, double sampleTime) {
  
  float u  = l1*x1prim + l2*x2prim + l3*x3prim + l4*x4prim; 

  // saturation
  if(u < -limit)  
    u = -limit; 
  else if(u > limit) 
    u = limit; 
    
  float x2 = getWheelRaw()/2; 
  float x1 = (x2-x2old)/sampleTime;
  x2old = x2; 
  float x4 = y;
  float x3 = (y-yold)/sampleTime;
  yold = y; 

  Serial.print("x1: ");
  Serial.print(x1);
  Serial.print(" x2: ");
  Serial.print(x2);
  Serial.print(" x3: ");
  Serial.print(x3);
  Serial.print(" x4: ");
  Serial.println(x4);

  x1prim = a11*x1+a12*x2+a13*x3+a14*x4+b1*u;           
  x2prim = a21*x1+a22*x2+a23*x3+a24*x4+b2*u;
  x3prim = a31*x1+a32*x2+a33*x3+a34*x4+b3*u;
  x4prim = a41*x1+a42*x2+a43*x3+a44*x4+b4*u ;  

  Serial.print("x1Prim: ");
  Serial.print(x1prim);
  Serial.print(" x2Prim: ");
  Serial.print(x2prim);
  Serial.print(" x3Prim: ");
  Serial.print(x3prim);
  Serial.print(" x4Prim: ");
  Serial.println(x4prim);
  
  return u;

}
