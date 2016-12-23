int carPosition = 0;
int pinCtrlCar[] = {};
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

void setup() {
  // set pinMode.
}

void loop() {
}
