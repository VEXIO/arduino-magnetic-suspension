int pinRayRcv[] = {9, 13}; // set pin of the ray receivers. be sure to set them on analog Pins but not digital pins.
int rayRcvThrehold = 50; // test when the ray is blocked, how will the signal be sent.
int raySignalCnt = 2; // how many ray signal is set.
int carPosition = 0;
int antiJitterDelay = 10; // change anti-jitter delay if needed. currently is 10ms. This should be usually more than 1ms, and less than 25ms.
void checkCarStatus(){
  int currentStatus;
  if (raySignalCnt == carPosition)
    return;
  currentStatus = analogRead(pinRayRcv[carPosition + 1]);
  if (currentStatus < rayRcvThrehold){ // determine < or > later
    delay(antiJitterDelay);
    currentStatus = analogRead(pinRayRcv[carPosition + 1]);
    if (currentStatus){
      carPosition++;
    }
  }
}

void setup() {
  // set pinMode.
}

void loop() {
  checkCarStatus();
}
