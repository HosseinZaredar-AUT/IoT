const int b0 = D1;
const int b1 = D2;
const int b2 = D3;

int counter = 7;

void setup() { 
   
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);

}

void loop() {

  counter++;
  if (counter == 8)
    counter = 0;

  char binary[4];
  int temp = counter + 8;
  itoa(temp, binary, 2);

  digitalWrite(b0, binary[3] == '1' ? HIGH : LOW);
  digitalWrite(b1, binary[2] == '1' ? HIGH : LOW);
  digitalWrite(b2, binary[1] == '1' ? HIGH : LOW);
  
  delay(1000);
  
}
