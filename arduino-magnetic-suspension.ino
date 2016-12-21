const int trig = 12;
const int echo = 13;
int reverseDistance = 1;
int time = 0;
boolean needReverse(){
  float duration, distance;
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration/2)/29;
  Serial.print("d(cm) = ");
  Serial.println(distance);
  if(distance <= reverseDistance)return true;
  else return false;
}

void setup() {
  Serial.begin(9600);
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
}

void loop() {
  while(!needReverse())
  	;
  // Do Reverse:
  	// pass;

}

