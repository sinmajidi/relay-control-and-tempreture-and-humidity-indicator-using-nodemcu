#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Galaxy A127724";
const char* password = "ezaz0462";

int gpio0_pin = 16; // D0 of nodemcu
int gpio1_pin = 14; //  D5 of nodemcu
int gpio2_pin = 12;// D6 of nodemcu
int gpio3_pin = 13; // D7 of nodemcu
int gpio4_pin = 5; // D1 of nodemcu
int gpio5_pin = 4; // D2 of nodemcu
int gpio6_pin = 15; // D8 of nodemcu
int gpio7_pin = 10;  // sd3 of nodemcu


//Your Domain name with URL path or IP address with path
String serverName = "http://cybele.ir/validate.php";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  pinMode(gpio0_pin,OUTPUT);
  pinMode(gpio1_pin,OUTPUT);
  pinMode(gpio2_pin,OUTPUT);
  pinMode(gpio3_pin,OUTPUT);
  pinMode(gpio4_pin,OUTPUT);
  pinMode(gpio5_pin,OUTPUT);
  pinMode(gpio6_pin,OUTPUT);
  pinMode(gpio7_pin,OUTPUT);
}

void loop() {
  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        for(int i=0;i<payload.length();i++)
        {
          Serial.println(payload[i]);
          if(i==0)
          {
            if(payload[i]=='1')
              digitalWrite(gpio0_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio0_pin,LOW);
          }
          if(i==1)
          {
            if(payload[i]=='1')
              digitalWrite(gpio1_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio1_pin,LOW);
          }
          if(i==2)
          {
            if(payload[i]=='1')
              digitalWrite(gpio2_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio2_pin,LOW);
          }
          if(i==3)
          {
            if(payload[i]=='1')
              digitalWrite(gpio3_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio3_pin,LOW);
          }
          if(i==4)
          {
            if(payload[i]=='1')
              digitalWrite(gpio4_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio4_pin,LOW);
          }
          if(i==5)
          {
            if(payload[i]=='1')
              digitalWrite(gpio5_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio5_pin,LOW);
          }
          if(i==6)
          {
            if(payload[i]=='1')
              digitalWrite(gpio6_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio6_pin,LOW);
          }
          if(i==7)
          {
            if(payload[i]=='1')
              digitalWrite(gpio7_pin,HIGH);
            if(payload[i]=='0')
              digitalWrite(gpio7_pin,LOW);
          }
        }
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
    lastTime = millis();
  }
}
