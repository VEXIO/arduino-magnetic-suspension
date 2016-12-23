int resetClock = 65284; // 65536 - 65535 / 1048 * 4
void setup() {
  // set pinMode.

  // start TIC.
  TCCR1A = 0;
  TCCR1B = 1<<CS12;
  TCNT1 = resetClock;
  bitSet(TIMSK1, TOIE1);
}

void loop() {
}

ISR(TIMER1_OVF_vect){
  // Things done here should not cause too many delay.
  show47digit(); // this should be put here for continuous refresh
  TCNT1 = resetClock;
}
