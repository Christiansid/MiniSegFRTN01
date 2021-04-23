const double gyroBias = 0.98;
const double accBias = 0.02;
double oldComp;
void compFilterSetup(){
  oldComp = 0;
}
double compFilter(double gyroDot, double alphaAccel){
  double dt = 1/samplingFreq;
  double compAlpha = gyroBias*(oldComp+gyroDot*dt) + accBias*alphaAccel;
  oldComp = compAlpha;
  return compAlpha;
}
