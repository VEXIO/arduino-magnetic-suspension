int pinBtn = 13; // set Pin for Btn.
int antiJitterDelay = 10; // change anti-jitter delay if needed. currently is 10ms. This should be usually more than 1ms, and less than 25ms.
int btnPressed = 0;
void checkBtnStatus(){
  int currentStatus = digitalRead(pinBtn);
  if (currentStatus != btnPressed){
    delay(antiJitterDelay);
    if (currentStatus == digitalRead(pinBtn)){
      btnPressed = currentStatus;
    }
  }
}

void setup() {
  // set pinMode.
}

void loop() {
  checkBtnStatus();
}
