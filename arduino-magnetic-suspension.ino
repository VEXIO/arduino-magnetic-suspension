int resetScd = 6;
int resetClock = 65536 - 65535 / 1048 * resetScd;

int digital[] = {48, 46, 44, 50}; // the wire pin for choosing the digit
int number[] = {32, 22, 36, 30, 34, 26, 24, 28}; // the wire for displaying number
int matrix[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246}; // combination of 0-9
int showNumber;

int pinBtn = 13; // set Pin for Btn.
int antiJitterDelay = 20; // change anti-jitter delay if needed. currently is 10ms. This should be usually more than 1ms, and less than 25ms.
int btnPressed = 0;

int carPosition = -1;
int pinCtrlCar[] = {};

int pinRayRcv[] = {A0, A1, A2, A3, A4}; // set pin of the ray receivers. be sure to set them on analog Pins but not digital pins.
int pinRaySnd = 37; // set pin of the ray sender.
int rayRcvThrehold = 500; // test when the ray is blocked, how will the signal be sent.
int raySignalCnt = 5; // how many ray signal is set.
int rayRcd[2]; // length should be the same as the raySignalCnt

int pinPowerSwitch[] = {41, 43, 45, 47, 49, 51, 53, 39}; // set pin of power setter

int currentSpeed;

void showNum(){
  static int i = 4;
  static int num = showNumber;
  digitalWrite(digital[i], LOW); // ignite this pin.
  i--;
  if (i == -1){
    num = showNumber;
    i = 3;
  }
  digitalWrite(digital[i], HIGH); // light the current digit pin
  showNum_show(num % 10, i);
  num /= 10;
}

void showNum_show(int num, int k){
  num = matrix[num];
  for (int i=7; i>=0; i--){
    digitalWrite(number[i], !(num%2));
    num /= 2;
  }
  if (k == 0){
    digitalWrite(number[7], LOW);
  }
}

void checkBtnStatus(){
  int currentStatus = digitalRead(pinBtn);
  if (currentStatus != btnPressed){
    delay(antiJitterDelay); // this is an anti-jitter delay for the mis-detection of the ray signals ( sudden misbehave )
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
  int power = !action; // high balance to enable
  digitalWrite(pinPowerSwitch[position], power);
}

void checkCarStatus(){
  int currentStatus;
  if (raySignalCnt == carPosition){
    return;
  }
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
  Serial.begin(9600);
  
  // set pinMode.
  // set pin for LED segbar.
  for (int i=0; i<4; i++){
    pinMode(digital[i], OUTPUT);
  }
  for (int i=0; i<8; i++){
    pinMode(number[i], OUTPUT);
  }

  /***************************************************************
   * set pin for the ray senders
   * as the ray sender will be positioned on the train
   * the ray sender will be always sending out signals
   * to the nearby ray receivers
   * and this won't cause too much pressure on the energy supply.
   **************************************************************/
  pinMode(pinRaySnd, OUTPUT);
  digitalWrite(pinRaySnd, HIGH);

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
