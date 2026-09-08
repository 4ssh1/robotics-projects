int lightIntensity = A5;
int buzzPin = 8;
int lightVol;
int delayTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(lightIntensity, INPUT);
  pinMode(buzzPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  lightVol = analogRead(lightIntensity);
  delayTime = (9./550.) * lightVol - (9. * 200. / 550.) + 1;

  Serial.println(delayTime);
  digitalWrite(buzzPin, HIGH);
  delay(delayTime);
  
  digitalWrite(buzzPin, LOW);
  delay(delayTime);

}
