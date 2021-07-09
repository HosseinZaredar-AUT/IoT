#include "ESP8266WiFi.h"e

const char *ssid = "Hossein's WiFi";
const char *password = "what963up";

void setup() {

  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  delay(2000);

  int n = WiFi.scanNetworks();

  if (n == 0) {
    Serial.println("There's no Wi-Fi network around you.");
  } else {
    Serial.printf("%d networks found:\n", n);
    for (int i = 0; i < n; i++) {
      Serial.printf("%d. ", i);
      Serial.println(WiFi.SSID(i));
    }
  }

  Serial.println();

  WiFi.begin(ssid, password);
  Serial.printf("Connecting to '%s'", ssid);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n");
  Serial.println("Connected!\nIP: ");
  Serial.println(WiFi.localIP());

}

void loop() {

}
