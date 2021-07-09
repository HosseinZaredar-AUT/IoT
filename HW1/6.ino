const int pwmPin = D6;

void setup() {
  
  Serial.begin(9600);
  analogWriteRange(100);

}

void loop() {
  
  int sensorValue = analogRead(A0);
  int waterLevel = (sensorValue * 100 ) / 1024;
  analogWrite(pwmPin, waterLevel);
  Serial.println(waterLevel);
  delay(10);

}
