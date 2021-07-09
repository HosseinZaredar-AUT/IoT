#include <SPI.h>
#include <MFRC522.h>

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN = D4;

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

String tag;

const char *ssid = "Hossein's WiFi";
const char *password = "what963up";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


void setup() {
  
  Serial.begin(9600);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected.");

  // Initialize a NTPClient to get time
  timeClient.begin();
  
  // Set offset time in seconds to adjust for your timezon
  // GMT +4:30 = 16200 seconds
  timeClient.setTimeOffset(16200);
  
  SPI.begin();
  rfid.PCD_Init();
  
}

void loop() {
  
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }

    // Getting current time
    
    timeClient.update();
    String formattedTime = timeClient.getFormattedTime();
    
    Serial.print(formattedTime);
    Serial.print(" -> ");
    Serial.println(tag);
    
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  delay(100);
  
}
