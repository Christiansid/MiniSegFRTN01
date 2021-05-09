const double gyroBias = 0.98;
const double accBias =  0.02;
const double bias = 0.10; 
double oldComp;
void compFilterSetup(){
  oldComp = 0;
}
double compFilter(double gyroDot, double alphaAccel){
  double dt = (double) samplingTime; //(double) 1/ (double) samplingFreq;
  double compAlpha = gyroBias*(oldComp+gyroDot*dt) + accBias*alphaAccel;
  oldComp = compAlpha;
  //Serial.println(compAlpha*100);
  return compAlpha;
}
