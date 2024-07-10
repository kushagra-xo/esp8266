#include "HardwareSerial.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <secrets.h>

const char* htmlContent = "<body><a href=/on><button>ON</button><a/><a href=/off><button>OFF</button></a></body>";

ESP8266WebServer server(80);  // Create a web server on port 80

void handleRoot() {
  server.send(200, "text/html", htmlContent);
}

void handleLEDOn() {
  digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (LOW is the voltage level, since the LED is active low)
  server.send(200, "text/plain", "LED is ON");
}

void handleLEDOff() {
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off (HIGH is the voltage level, since the LED is active low)
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED pin as an output

  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
