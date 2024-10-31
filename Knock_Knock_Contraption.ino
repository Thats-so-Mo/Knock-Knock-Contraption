/*MIT License

Copyright (c) 2024 That's So Mo
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This code has been modified by That's So Mo to be "suited" for the "Ghost Knock trick".
This code will configure ESP8266 in SoftAP mode and will act as a web server for atleast two connecting devices. Indiviual will then be allowed to turn On/Off the vib.
 */
 
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Specifying the SSID and Password of the AP */
const char* ssid = "SamandColby1043"; // Access Point SSID
const char* password = "Test123456"; // Access Point Password
uint8_t max_connections = 5; // Maximum Connection Limit for AP
int current_stations = 0, new_stations = 0;

// Specifying the Webserver instance to connect with HTTP Port: 80
ESP8266WebServer server(80);

// Specifying the Pins connected from vibrators to Wemos
uint8_t sole1_pin = D1;
uint8_t sole2_pin = D3;

// Specifying the boolean variables indicating the status of wemos to solenoids
bool sole1_status = false;
bool sole2_status = false;

void setup() {
  // Start the serial communication channel
  Serial.begin(115200);
  Serial.println();

  // Output mode for the Solenoid Pins
  pinMode(sole1_pin, OUTPUT);
  pinMode(sole2_pin, OUTPUT);

  // Setting the AP Mode with SSID, Password, and Max Connection Limit
  if (WiFi.softAP(ssid, password, 1, false, max_connections) == true) {
    Serial.print("Access Point is Created with SSID: ");
    Serial.println(ssid);
    Serial.print("Max Connections Allowed: ");
    Serial.println(max_connections);
    Serial.print("Access Point IP: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Unable to Create Access Point");
  }

  // Specifying the functions which will be executed upon corresponding GET request from the client
  server.on("/", handle_OnConnect);
  server.on("/soleyes", handle_soleyes);
  server.on("/soleno", handle_soleno);
  server.onNotFound(handle_NotFound);

  // Starting the Server
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  // Assign the server to handle the clients
  server.handleClient();

  // Continuously check how many stations are connected to Soft AP and notify whenever a new station is connected or disconnected
  new_stations = WiFi.softAPgetStationNum();

  if (current_stations < new_stations) { // Device is Connected
    current_stations = new_stations;
    Serial.print("New Device Connected to SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }

  if (current_stations > new_stations) { // Device is Disconnected
    current_stations = new_stations;
    Serial.print("Device disconnected from SoftAP... Total Connections: ");
    Serial.println(current_stations);
  }

  // Turn the solenoids OFF by default
  digitalWrite(sole1_pin, LOW);
  digitalWrite(sole2_pin, LOW);
}

void handle_OnConnect() {
  Serial.println("Client Connected");
  server.send(200, "text/html", HTML());
}

void handle_soleyes() {
  Serial.println("sole Yes");
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, HIGH);
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, LOW);
  digitalWrite(sole2_pin, HIGH);
  delay(20);
  digitalWrite(sole2_pin, LOW);
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, HIGH);
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, LOW);
  digitalWrite(sole2_pin, HIGH);
  delay(20);
  digitalWrite(sole2_pin, LOW);
  sole1_status = false;
  sole2_status = false;
  server.send(200, "text/html", HTML());
}

void handle_soleno() {
  Serial.println("sole NO");
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, HIGH);
  delay(random(1, 7) * 1000);
  digitalWrite(sole1_pin, LOW);
  digitalWrite(sole2_pin, HIGH);
  delay(20);
  digitalWrite(sole2_pin, LOW);
  sole1_status = false;
  sole2_status = false;
  server.send(200, "text/html", HTML());
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String HTML() {
  String msg = "<!DOCTYPE html> <html>\n";
  msg += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  msg += "<title>The Ghost Knock Contraption Server</title>\n";
  msg += "<style>html{font-family:Helvetica; display:inline-block; margin:0px auto; text-align:center; background-color:#2B2934;}\n";
  msg += "body{margin-top: 50px;} h1{color: #000000; margin: 50px auto 30px;} h3{color:#000000; margin-bottom: 50px;}\n";
  msg += ".button{display:block; width:80px; background-color:#f48100; border:none; color:white; padding: 13px 30px; text-decoration:none; font-size:25px; margin: 0px auto 35px; cursor:pointer; border-radius:4px;}\n";
  msg += ".button-on{background-color:#26282d;}\n";
  msg += ".button-on:active{background-color:#26282d;}\n";
  msg += ".button-off{background-color:#000000;}\n";
  msg += ".button-off:active{background-color:#000000;}\n";
  msg += "</style>\n";
  msg += "</head>\n";
  msg += "<body>\n";
  msg += "<h1>The Ghost Knock Contraption Server</h1>\n";
  msg += "<h3>Using Access Point (AP) Mode</h3>\n";
  msg += "<p><a class=\"button button-on\" href=\"/soleyes\">Yes</a></p>\n";
  msg += "<p><a class=\"button button-off\" href=\"/soleno\">No</a></p>\n";
  msg += "</body>\n";
  msg += "</html>\n";
  return msg;
}
