#include "ESP8266WiFi.h"

const char *ssid = "Hossein's WiFi";
const char *password = "what963up";

WiFiServer server(80);

String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

float ldrValue; 

void setup() {

  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.mode(WIFI_STA);
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.printf("Connecting to '%s'", ssid);

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\n");
  Serial.print("Connected!\nIP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  
}

void loop() {

  WiFiClient client = server.available();

  if (client) {

    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    ldrValue = -1;

    while (client.connected() && currentTime - previousTime <= timeoutTime) {

      currentTime = millis();         
      if (client.available()) {
      
        char c = client.read();
        header += c;

        if (c == '\n') { 

          if (currentLine.length() == 0) {

            if (header.indexOf("GET /led/on") >= 0) {
              digitalWrite(LED_BUILTIN, LOW);
            } else if (header.indexOf("GET /led/off") >= 0) {
              digitalWrite(LED_BUILTIN, HIGH);
            } else if (header.indexOf("GET /ldr") >= 0) {
              int sensorValue = analogRead(A0);
              ldrValue = (sensorValue * 100) / 1024;
            }
              
            client.println(
              "HTTP/1.1 200 OK\n"
              "Content-type:text/html\n"
              "Connection: close\n"
              "\n"
              "<!DOCTYPE html><html>\n"
              "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
              "<link rel=\"icon\" href=\"data:,\">\n"
              "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n"
              ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;\n"
              "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\n"
              ".button2 {background-color: #77878A; padding: 16px 34px;}</style></head>\n"
              "<body><h1>ESP8266 Web Server</h1>"
            );

            if (ldrValue == -1) {
              client.println("<p><a href=\"/ldr\"><button class=\"button\">LDR</button></a></p>\n"); 
            } else {
              client.print("<p><a href=\"/ldr\"><button class=\"button\">LDR: ");
              client.print(ldrValue); 
              client.print("</button></a></p>\n"); 
            }

            client.println(
              "<p><a href=\"/led/on\"><button class=\"button\">LED ON</button></a></p>\n"
              "<p><a href=\"/led/off\"><button class=\"button button2\">LED OFF</button></a></p>\n"
              "</body></html>"
            );
            
            client.println();

          } else {
            currentLine = "";
          }     
          
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    } 

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

  }

  delay(2000);

}
