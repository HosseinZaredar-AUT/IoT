#include "ESP8266WiFi.h"

IPAddress apIP(10, 10, 10, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {

  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  delay(1000);
  
  WiFi.softAP("NodeMCU", "123123123");
  delay(1000);

  Serial.print("Initial IP: ");
  Serial.println(WiFi.softAPIP());

  delay(1000);
  WiFi.softAPConfig(apIP, apIP, subnet);
  Serial.print("Static IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println();

}

void loop() {

}
