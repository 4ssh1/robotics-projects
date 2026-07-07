// Each entry maps a *bit position* to a *physical Arduino pin*.
// The array INDEX (0,1,2,3) is what matters for binary place value —
// the PIN NUMBER (2,3,4,5) is just which wire it happens to be wired to.
//
//   array index 0 -> ones place  (2^0) -> wired to physical pin 2
//   array index 1 -> twos place  (2^1) -> wired to physical pin 3
//   array index 2 -> fours place (2^2) -> wired to physical pin 4
//   array index 3 -> eights place(2^3) -> wired to physical pin 5
const int ledPins[] = {2, 3, 5, 6}; 
const int numPins = 4; 

void setup() {
  // Use a loop to set all pins as OUTPUT without repeating code
  for (int i = 0; i < numPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Count from 1 to 15 (the max a 4-bit binary number can represent: 1111)
  for (int number = 1; number <= 15; number++) {
    displayBinary(number);
    delay(1000);
  }
}

void displayBinary(int num) {
  // bitRead(value, bitPosition) returns the bit at 'bitPosition' in 'value',
  // counting from the right (bit position 0 = least significant bit, i.e.
  // the ones place / 2^0). Internally it does (value >> bitPosition) & 1 —
  // shift the target bit down to position 0, then mask off everything else.
  //
  // 'i' below is a BIT POSITION / ARRAY INDEX, not a pin number.
  // ledPins[i] looks up which physical pin that bit position controls.
  //
  // Example for number 6 (Binary: 0110):
  //   i=0 -> bitRead(6,0) -> ones place  -> 0 -> ledPins[0] (pin 2) LOW
  //   i=1 -> bitRead(6,1) -> twos place  -> 1 -> ledPins[1] (pin 3) HIGH
  //   i=2 -> bitRead(6,2) -> fours place -> 1 -> ledPins[2] (pin 4) HIGH
  //   i=3 -> bitRead(6,3) -> eights place-> 0 -> ledPins[3] (pin 5) LOW
  //   (0*8 + 1*4 + 1*2 + 0*1 = 6 ✓)
  
  for (int i = 0; i < numPins; i++) {
    if (bitRead(num, i) == 1) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}