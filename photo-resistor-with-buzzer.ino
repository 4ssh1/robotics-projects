int lightIntensity = A5;
int buzzPin = 8;
int lightVol;
int delayTime;

void setup() {
  pinMode(lightIntensity, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Reads voltage across the photoresistor.
  // Because Ir circuit is 5V -> 4k Resistor -> A5 -> Photoresistor -> GND:
  // - High light = Low LDR resistance = Low analog reading (around 200)
  // - Low light = High LDR resistance = High analog reading (around 750)
  lightVol = analogRead(lightIntensity);
  
  // LINEAR MAPPING (y = mx + b):
  // I noticed distinct buzzer tones at 1ms and 10ms delays. 
  // This formula perfectly maps Ir observed analog readings to those specific delays:
  // - When lightVol is 200, the math results in exactly 1 (1ms delay)
  // - When lightVol is 750, the math results in exactly 10 (10ms delay)
  // Equation breakdown: slope is (10-1)/(750-200) = 9/550.
  delayTime = (9./550.) * lightVol - (9. * 200. / 550.) + 1;

  Serial.println(delayTime);
  
  // Toggling a passive buzzer creates sound waves. The delay time dictates the frequency (pitch).
  // - 1ms delay creates a fast toggle = high frequency/pitch (~500 Hz tone)
  // - 10ms delay creates a slow toggle = low frequency/pitch (~50 Hz tone)
  digitalWrite(buzzPin, HIGH);
  delay(delayTime);
  
  digitalWrite(buzzPin, LOW);
  delay(delayTime);
}