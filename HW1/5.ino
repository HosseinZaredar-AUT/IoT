const int pwmPin = D6;

void setup() {
  
  Serial.begin(9600);
  analogWriteRange(100);

}

void loop() {
  
  int sensorValue = analogRead(A0);
  float brightness = (sensorValue * 100) / 1024; 
  Serial.println(brightness);
  analogWrite(pwmPin, 100 - brightness);
  delay(10);
  
}
