#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

//setup button
int button = 16;
int stat = 0;

//Domain to GET
String serverName = "http://yoururl/LED=";

void setup() {
  Serial.begin(115200);

  pinMode(button, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Server:" + serverName);
  Serial.println("Waiting For Button Press");
}

void loop() {
  stat = digitalRead(button);

  if (stat == HIGH) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + "ON";
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
  }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}
