#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* pass = "";

const char* serverUrl = "https://s-m.com.sa/r.html"; 
unsigned const long interval = 2000;
unsigned long zero = 0;
const int yellowled = 26; 
const int orangeled = 25; 
const int purpleled = 33; 
const int blueled = 32; 
const int greenled = 27; 

void setup() {
  Serial.begin(115200);
  pinMode(greenled, OUTPUT); 
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println(".");
  }
  Serial.println("WiFi Connected!");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() - zero > interval) {
    HTTPClient http;
    http.begin(serverUrl);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.print("Server Response: ");
      Serial.println(payload);

      if (payload == "forward") {
        digitalWrite(yellowled, HIGH);
        Serial.println("forward LED Turned ON");
      } else if (payload == "backward") {
        digitalWrite(orangeled, HIGH); 
        Serial.println("backward LED Turned on");
      }else if (payload == "stop") {
        digitalWrite(purpleled, HIGH); 
        Serial.println("stop LED Turned on");
      }else if (payload == "left") {
        digitalWrite(blueled, HIGH); 
        Serial.println("left LED Turned on");
      } else if (payload == "right") {
        digitalWrite(greenled, HIGH); 
        Serial.println("right LED Turned on");
      } else {
        Serial.println("Invalid command");
      }
    } else {
      Serial.print("Error fetching data: ");
      Serial.println(httpResponseCode);
    }
    zero = millis();
  }
}