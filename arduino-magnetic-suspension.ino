int resetClock = 65284; // 65536 - 65535 / 1048 * 4

int digital[] = {13, 10, 9, 7}; // the wire pin for choosing the digit
int number[] = {12, 8, 5, 3, 2, 11, 6, 4}; // the wire for displaying number
int matrix[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246}; // combination of 0-9
int showNumber;

int pinBtn = 13; // set Pin for Btn.
int antiJitterDelay = 10; // change anti-jitter delay if needed. currently is 10ms. This should be usually more than 1ms, and less than 25ms.
int btnPressed = 0;

int carPosition = 0;
int pinCtrlCar[] = {};

int pinRayRcv[] = {9, 13}; // set pin of the ray receivers. be sure to set them on analog Pins but not digital pins.
int rayRcvThrehold = 50; // test when the ray is blocked, how will the signal be sent.
int raySignalCnt = 2; // how many ray signal is set.


void showNum(){
  static int i = 0;
  int num = showNumber;
  digitalWrite(digital[i], HIGH); // light the current digit pin
  showNum_show(num % 10, i);
  num /= 10;
  delay(5);
  showNum_igniteAll(); // ignite all to show the next digit.
}

void showNum_show(int num, int k){
  num = matrix[num];
  for (int i=7; i>=0; i--){
    digitalWrite(number[i], !(num%2));
    num /= 2;
  }
  if (k == 1)
    digitalWrite(4, LOW);
}

void showNum_igniteAll(){
  for (int i=2; i<=13; i++)
    digitalWrite(i, LOW);
}

void checkBtnStatus(){
  int currentStatus = digitalRead(pinBtn);
  if (currentStatus != btnPressed){
    delay(antiJitterDelay);
    if (currentStatus == digitalRead(pinBtn)){
      btnPressed = currentStatus;
    }
  }
}

void changePower(){
  static int lastPosition = 0;
  if (lastPosition != carPosition){
    changePower_switch(lastPosition, LOW);
    changePower_switch(carPosition, HIGH);
    lastPosition = carPosition;
  }
}

void changePower_switch(int position, int action){
  // don't know what to do before seeing the parts.
}

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

  // start TIC.
  TCCR1A = 0;
  TCCR1B = 1<<CS12;
  TCNT1 = resetClock;
  bitSet(TIMSK1, TOIE1);
}

void loop() {
  checkBtnStatus();
  changePower();
  checkCarStatus();
}

ISR(TIMER1_OVF_vect){
  // Things done here should not cause too many delay.
  showNum(); // this should be put here for continuous refresh
  TCNT1 = resetClock;
}
