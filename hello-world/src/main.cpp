#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <secrets.h>

ESP8266WebServer server(80);
void handleRoot(){
	server.send(200, "text/plain", "Hello, World!");
}
void setup(){
	Serial.begin(9600);
	WiFi.begin(ssid, password);
	server.on("/", handleRoot);
	server.begin();
}

void loop(){
	server.handleClient();
}
