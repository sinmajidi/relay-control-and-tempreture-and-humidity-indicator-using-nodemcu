#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>


void writeString(int address, String data);
String readString(int address);




int gpio0_pin = 16; // D0 of nodemcu
int gpio1_pin = 14; //  D5 of nodemcu
int gpio2_pin = 12;// D6 of nodemcu
int gpio3_pin = 13; // D7 of nodemcu
int config_pin = 15; // D8 of nodemcu


String network="";
String serverName;
String security_code="AzpH4798@";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

ESP8266WebServer server(80);
WiFiClient client;
HTTPClient http;






bool is_authentified() {
  Serial.println("Enter is authentified");
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}


void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    Serial.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == readString(200) &&  server.arg("PASSWORD") == readString(225) ) 
    {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
      return;

    }

    msg = "Wrong username/password! try again.";
    Serial.println("Log in Failed");
  }
   String content = R"***(
   <!DOCTYPE html> <html>
  <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">
  <title>AFRA remote control</title>
  <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
.forget {border: 1px solid #8F037A;padding:10px;color:#8F037A;border-radius:10px;font-size: 1.2em;text-decoration: none;}
.forget:hover {background-color:#8F037A;color:#fff;}
</style>
  </head>
  <body style='background-color:#96aedd'><form action='/login' method='POST'><p  align ='center' style='font-size:300%;'><b>  Welcome to future  </b></p><br>
  <p  align ='center' style='font-size:300%;'><b>  Let's Login to continue...  </b></p><br>
  <p   align ='center' style='font-size:160%'><b> UserName: <input type='text' name='USERNAME' placeholder='user name' required></b></p><br>
  <p  align ='center' style='font-size:160%'><b>Password: <input type='password' name='PASSWORD' placeholder='password' required></b></p><br>
  <p  align ='center' style='font-size:160%'><input style='border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;' type='submit' name='submit' value='Log in'></form></p><br>
  <br><br><hr><br>forget password??? <a class="forget" href="/forget">forget</a>
  </body></html>
  )***";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot() {
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
 String content = R"***(
<!DOCTYPE html> <html>
<head><meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>AFRA Relay Control</title>
<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
body{margin-top: 50px;background-color:#96aedd;}
.button {display: inline-block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 0px;cursor: pointer;border-radius: 10px;}
.button-on {background-color: #1abc9c;}
.button-on:active {background-color: #16a085;}
.button-off {background-color: #34495e;}
.button-off:active {background-color: #2c3e50;}
p {font-size: 1.2em;color: #000;margin-bottom: 1%;}
.log_out {border: 1px solid red;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;text-decoration: none;}
.log_out:hover {background-color:#ff0000;color:#fff;}
.change {border: 1px solid #8F037A;padding:10px;color:#8F037A;border-radius:10px;font-size: 1.2em;text-decoration: none;}
.change:hover {background-color:#8F037A;color:#fff;}
</style>
</head>
<body>

<form action='/change_info' method='POST'><p  align ='center' style='font-size:300%;'>
  <p   align ='center' style='font-size:160%'><b> SSID: <input type='text' name='SSID' placeholder='ssid' required></b></p><br>
  <p  align ='center' style='font-size:160%'><b> network Password: <input type='password' name='NET_PASSWORD' placeholder='password' required></b></p><br>
  <p  align ='center' style='font-size:160%'><b> the server path: <input type='text' name='path' placeholder='server path' required></b></p><br>
  <p  align ='center' style='font-size:160%'><input style='border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;' type='submit' name='submit' value='change'></form></p><br>
  <br><hr><br>You can access this page until you <a class="log_out" href="/login?DISCONNECT=YES">Log Out</a>
</body></html>
)***";
  server.send(200, "text/html", content);
}

//no need authentification
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}



void writeString(int address, String data)
{
  int stringSize = data.length();
  for(int i=0;i<stringSize;i++)
  {
    EEPROM.write(address+i, data[i]);
  }
  EEPROM.write(address + stringSize,'\0');   //Add termination null character
 EEPROM.commit();
}


String readString(int address)
{
  char data[100]; //Max 100 Bytes
  int len=0;
  unsigned char k;
  k = EEPROM.read(address);
  while(k != '\0' && len < 100)   //Read until null character
  {
    k = EEPROM.read(address + len);
    data[len] = k;
    len++;
  }
  data[len]='\0';
  return String(data);
}







void setup() {
 
  Serial.begin(115200); 
  EEPROM.begin(512);
  pinMode(gpio0_pin,OUTPUT);
  pinMode(gpio1_pin,OUTPUT);
  pinMode(gpio2_pin,OUTPUT);
  pinMode(gpio3_pin,OUTPUT);
  pinMode(config_pin,INPUT);
  network="internet";
  
  
  
}



void loop() {
  if(digitalRead(config_pin)==HIGH)
  {
      configuration();
      network="local";
  }
  if(network=="local")
      server.handleClient();
  if(network=="internet")
  {
    if(WiFi.status() != WL_CONNECTED)
      server_conection();
    server_get_data();
  }
      
  
}

void forget()
{
  
   if (server.hasArg("security")) {
   if(server.arg("security")==security_code)
    server.sendHeader("Location", "/change_username_and_password");
   else
    server.sendHeader("Location", "/forget");
    server.send(301);
      Serial.println("username and password change Successfuly");
      return;
  }



  
  String content = R"***(
   <!DOCTYPE html> <html>
  <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">
  <title>AFRA remote control</title></head>
  <body style='background-color:#CE67D3'><form action='/forget' method='POST'><p  align ='center' style='font-size:300%;'><b>  Welcome to future  </b></p><br>
  <p  align ='center' style='font-size:300%;'><b>  please enter your security code  </b></p><br>
  <p   align ='center' style='font-size:160%'><b> security code <input type='text' name='security' placeholder='security code' required></b></p><br>
  <p  align ='center' style='font-size:160%'><input style='border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;' type='submit' name='submit' value='check'></form></p><br> </body></html>
  )***";
   server.send(200, "text/html", content);
}

void change_username_and_password()
{

  if (server.hasArg("NEW_USERNAME") && server.hasArg("NEW_PASSWORD")) {
    writeString(200, server.arg("NEW_USERNAME"));
    writeString(225, server.arg("NEW_PASSWORD"));
    server.sendHeader("Location", "/");
    server.send(301);
      Serial.println("username and password change Successfuly");
      return;
  }
  
  String content = R"***(
   <!DOCTYPE html> <html>
  <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">
  <title>AFRA remote control</title></head>
  <body style='background-color:#CE67D3'><form action='/change_username_and_password' method='POST'><p  align ='center' style='font-size:300%;'><b>  Welcome to future  </b></p><br>
  <p  align ='center' style='font-size:300%;'><b>  Let's change username and password  </b></p><br>
  <p   align ='center' style='font-size:160%'><b> UserName: <input type='text' name='NEW_USERNAME' placeholder='new user name' required></b></p><br>
  <p  align ='center' style='font-size:160%'><b>Password: <input type='password' name='NEW_PASSWORD' placeholder='new password' required></b></p><br>
  <p  align ='center' style='font-size:160%'><input style='border: 1px solid red;background-color:transparent;padding:10px;color:#ff0000;border-radius:10px;font-size: 1.2em;' type='submit' name='submit' value='change'></form></p><br> </body></html>
  )***";
  server.send(200, "text/html", content);
}


void configuration()
{
  Serial.print("Access point configuration...");
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("AFRA","admin1234") ? "Ready" : "Failed!");
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/change_info", change_info);
  server.on("/change_username_and_password", change_username_and_password);
//  server.on("/change_wifi_password",  change_wifi_password);
  server.on("/forget",forget);
//  server.on("/forget_wifi_info",forget_wifi_info);
//  server.onNotFound(handleNotFound);

  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  server.collectHeaders(headerkeys, headerkeyssize );
  server.begin();
  Serial.println("HTTP server starting.");
  return;
}







void server_conection()
{
  WiFi.begin(readString(100), readString(125));
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  return;
}




void server_get_data()
{
   String serverName = readString(150);
   // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode) {
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
    lastTime = millis();
  }
  return;
}

void change_info()
{
  if (server.hasArg("SSID") && server.hasArg("NET_PASSWORD")&& server.hasArg("path")) {
    writeString(100,server.arg("SSID"));
    writeString(125,server.arg("NET_PASSWORD"));
    writeString(150,server.arg("path"));
    server.sendHeader("Location", "/");
    server.send(301);
      Serial.println("ssid and password change Successfuly");
      return;
  }
  handleRoot();
}
