#include <ESP8266WiFi.h>

#define sensorPin A0
const char* ssid = "Le1S";
const char* pass = "!87654321faH#";
const char* host = "192.168.43.41";

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  pinMode(A0, INPUT);
  WiFi.begin(ssid, pass);

  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.print(WiFi.localIP());
}
void loop() {
  delay(3000);
  int val = analogRead(sensorPin);

  WiFiClient client;
  const int httpPort = 3000;
  if(!client.connect(host, httpPort)){
    Serial.println("Connection failed!");
    return;
    }
  String url = "/";

  String data = "reading=" + String(val);
  Serial.print("Requesting POST...");
  //HTTP Header for POST request
  client.println("POST / HTTP/1.1");
  client.println("Host: server_name");
  client.println("Accept: */*");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.print(data);

 unsigned long timeout = millis();
 while (client.available() == 0) {
 if (millis() - timeout > 5000) {
  Serial.println(">>> Client Timeout !");
  client.stop();
  return;
 }
}
// Read all the lines of the reply from server and print them to Serial
 while(client.available()){
  String line = client.readStringUntil('\r');
  Serial.print(line);
 }

 Serial.println();
 Serial.println("closing connection");
}
