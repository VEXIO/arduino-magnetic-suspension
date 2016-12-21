int digital[] = {13, 10, 9, 7}; // the wire pin for choosing the digit
int number[] = {12, 8, 5, 3, 2, 11, 6, 4}; // the wire for displaying number
int matrix[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246}; // combination of 0-9
int showNumber;

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

void setup() {
  Serial.begin(9600);

  // just enable all the pins
  for (int i=2; i<=13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  showNum(); // this takes 5ms to process
}

