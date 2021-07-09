const int buzzerPin = D1;

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  
  int sensorValue = analogRead(A0);
  float brightness = (sensorValue * 100) / 1024;
  
  Serial.println(brightness);
  
  if (brightness > 50) {
    digitalWrite(LED_BUILTIN, LOW);
    tone(buzzerPin, 110);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    noTone(buzzerPin);
  }
  
  delay(10);
  
}
