
# include <MPU6050.h>
# include <Wire.h>
class HighPassFilter
{
public:
    HighPassFilter(float reduced_frequency)
    : alpha(1-exp(-2*M_PI*reduced_frequency)), y(0) {}
    float operator()(float x) {
        y += alpha*(x-y);
        return x-y;
    }
    void setAlpha(float reduced_frequency){
      alpha = 1-exp(-2*M_PI*reduced_frequency);
     }
private:
    float alpha, y;
};

HighPassFilter highPassX(5/100);

MPU6050 mpu;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial.println("Initializing MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)){
    //Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
}
    // Calibrate gyroscope. The calibration must be at rest.
    // If you don't want calibrate, comment this line.
    mpu.calibrateGyro();
    checkSettings();
      Serial.print("Yraw:,Zraw:");

}

void loop() {
  Vector rawGyro = mpu.readRawGyro();
  //Serial.print(" Xraw:");
  //Serial.print(rawGyro.XAxis);
  Serial.println(rawGyro.YAxis);
  Serial.print(",");
  //Serial.print("Zraw:");
  Serial.println(rawGyro.ZAxis);
  //Serial.print("Filtered:");
  //Serial.println(highPassX(zraw));
  //int raw = rawGyro.ZAxis;
  //int filtered = highPassX(rawGyro.YAxis);
  //if(raw != filtered){
    //Serial.print(" Zraw = ");
    //Serial.print(raw);
    //Serial.print(" Zfiltered = ");
    //Serial.println(filtered);
 
  //Serial.println(" XFiltered = ");
  //Serial.println(highPassX(rawGyro.XAxis));
  if(Serial.available()>0){
    highPassX.setAlpha(Serial.read()/100);
  }
  delay(10);

}
void checkSettings() {
 // Serial.println();
  
 // Serial.print(" * Sleep Mode:        ");
  //Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  //Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
  case MPU6050_CLOCK_KEEP_RESET:  break;   //Serial.println("Stops the clock and keeps the timing generator in reset"); break;
  case MPU6050_CLOCK_EXTERNAL_19MHZ: break; //Serial.println("PLL with external 19.2MHz reference"); break;
  case MPU6050_CLOCK_EXTERNAL_32KHZ:break; //Serial.println("PLL with external 32.768kHz reference"); break;
  case MPU6050_CLOCK_PLL_ZGYRO:    break; // Serial.println("PLL with Z axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_YGYRO:     break; //Serial.println("PLL with Y axis gyroscope reference"); break;
  case MPU6050_CLOCK_PLL_XGYRO:     break; //Serial.println("PLL with X axis gyroscope reference"); break;
  case MPU6050_CLOCK_INTERNAL_8MHZ:  break;//Serial.println("Internal 8MHz oscillator"); break;
  }
  
 // Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
  case MPU6050_SCALE_2000DPS:  break;      //Serial.println("2000 dps"); break;
  case MPU6050_SCALE_1000DPS:   break;     //Serial.println("1000 dps"); break;
  case MPU6050_SCALE_500DPS:    break;     //Serial.println("500 dps"); break;
  case MPU6050_SCALE_250DPS:     break;    //Serial.println("250 dps"); break;
  }
  
 // Serial.print(" * Gyroscope offsets: ");
  //Serial.print(mpu.getGyroOffsetX());
 // Serial.print(" / ");
 // Serial.print(mpu.getGyroOffsetY());
 // Serial.print(" / ");
  //Serial.println(mpu.getGyroOffsetZ());
  
 // Serial.println();
  }
