byte encoder1;
byte encoder2;
uint8_t oldState;
long ticks;
void setupWheel(){
  oldState = 0;
  ticks = 0;
  pinMode(wheelEncoderPin1, INPUT);
  pinMode(wheelEncoderPin2,INPUT);
  attachInterrupt(digitalPinToInterrupt(wheelEncoderPin1), encoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(wheelEncoderPin2), encoderInterrupt, CHANGE);
}

void encoderInterrupt(){
  //encoder1++;
  uint8_t newState;
  newState = (digitalRead(wheelEncoderPin1));
  newState |= (digitalRead(wheelEncoderPin2)<<1);
  switch(newState){
    case 0:
      //Wheel moving backward
      if(oldState == 1){
        ticks--;
      }else{
        //Wheel is moving forward
        ticks++;
      }
      break;
    case 1:
     if(oldState == 3){
      //Moving backward
      ticks--;
     }else{
      //Moving forward
      ticks++;
     }
     break;
   case 2:
    if(oldState == 0){
      //Moving backward
      ticks--;
    }else{
      ticks++;
    }
    break;
  case 3:
    if(oldState == 2){
      //Moving backward
      ticks--;
    }else{
      ticks++;
    }
  }
  oldState = newState;
  //Serial.println(ticks);
}
long getWheelRaw(){
  return ticks;
}
