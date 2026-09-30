byte btn1 = 12;
byte btn2 = 10;
byte led = 6;
int bright = 0;
int buzz = 2;

int btnVal1;
int btnVal2;

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT); // use external pull-up resistor or change type
  pinMode(btn2, INPUT); // use external pull-up resistor or change type
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  btnVal1 = digitalRead(btn1);
  btnVal2 = digitalRead(btn2);

  Serial.print("btn1 = ");
  Serial.print(btnVal1);
  Serial.print(", ");
  Serial.print("btn2 = ");
  Serial.println(btnVal2);
  delay(150);

  // 1. Adjust brightness on button press
  if (btnVal1 == 0) {
    bright += 10;
  } else if (btnVal2 == 0) {
    bright -= 10;
  }

  // 2. Clamp boundaries and trigger buzzer BEFORE writing to the LED
  if (bright > 255) {
    bright = 255;
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    Serial.println("Too high");
  }

  if (bright < 0) {
    bright = 0;
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    Serial.println("Too low");
  }

  // 3. Write the safe, clamped value to the LED pin
  analogWrite(led, bright);
  Serial.println(bright);
}