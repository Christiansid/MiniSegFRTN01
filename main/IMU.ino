
#include <MPU6050.h>

MPU6050 mpu;

// Imu bias
// Accelometer bias
const int16_t accelZBias = 710; //-17200;
const int16_t accelYBias = -100;
//Gyroscope bias
const int16_t xVelBias = 44; //210; //39;

//Gyroscope scaling factor
const double scaleGyro = 1.34*pow(10, -4);
//const double scaleGyro = 0.028647; 

const float scaleAcc = 16384;

//Setup IMU board
void IMUSetup() {
 
  //Serial.println("Initializing MPU6050");
  while(!mpu.begin(MPU6050_SCALE_250DPS, MPU6050_RANGE_2G)){
    //Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
    // Calibrate gyroscope. The calibration must be at rest.
    // If you don't want calibrate, comment this line.
    mpu.calibrateGyro();
    checkSettings();

}
void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:        ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:      ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Gyroscope:         ");
  switch(mpu.getScale())
  {
    case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;
    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;
    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;
    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
  } 
  
  Serial.print(" * Gyroscope offsets: ");
  Serial.print(mpu.getGyroOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getGyroOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getGyroOffsetZ());
  
  Serial.println();
}
float getGyroDot(){
  // Testa ändra skalfaktor
  Vector rawGyro = mpu.readRawGyro();
  double x = (double) rawGyro.XAxis + xVelBias;
  x = x*scaleGyro;
  return x;
  
}
float getAlphaAccel(){
  Vector rawAccel = mpu.readRawAccel();
  float y = rawAccel.YAxis + accelYBias;
  y = y/scaleAcc; 
  float z = rawAccel.ZAxis + accelZBias;
  z = z/scaleAcc; 
  float alpha = (float) atan2(z, -y);
  return alpha;
}
