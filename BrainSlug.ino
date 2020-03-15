#include <IRremoteESP8266.h>

#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

ESP8266WebServer server(80);

IRsend irsend(16);

void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.setTimeout(180);
    if(!wifiManager.autoConnect())
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      ESP.reset();
      delay(5000);
    }
    Serial.print("Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    
    server.on("/remote/power", [](){
      irsend.sendNEC(0x807FE01F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/play", [](){
      irsend.sendNEC(0x807F20DF, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/clock", [](){
      irsend.sendNEC(0x807FA05F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/timer", [](){
      irsend.sendNEC(0x807F807F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/auto", [](){
      irsend.sendNEC(0x807F40BF, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/spot", [](){
      irsend.sendNEC(0x807FC03F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/turbo", [](){
      irsend.sendNEC(0x807FB04F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/corner", [](){
      irsend.sendNEC(0x807F708F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/base", [](){
      irsend.sendNEC(0x807F609F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/up", [](){
      irsend.sendNEC(0x807F10EF, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/down", [](){
      irsend.sendNEC(0x807F906F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/left", [](){
      irsend.sendNEC(0x807FD02F, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/right", [](){
      irsend.sendNEC(0x807F50AF, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
    
    server.on("/remote/ok", [](){
      irsend.sendNEC(0x807F30CF, 32);
      server.send(200, "application/vnd.api+json", "{ \"status\": \"success\" }");
    });
  
    server.onNotFound([](){
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server.uri();
      message += "\nMethod: ";
      message += (server.method() == HTTP_GET)?"GET":"POST";
      message += "\nArguments: ";
      message += server.args();
      message += "\n";
      for (uint8_t i=0; i<server.args(); i++){
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
      }
      server.send(404, "text/plain", message);
    });
  
    irsend.begin();
    Serial.println("Irsend started");
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
