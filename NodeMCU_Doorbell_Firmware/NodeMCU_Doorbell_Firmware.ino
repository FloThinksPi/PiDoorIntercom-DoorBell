#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "pw";
const boolean dhcp = false; // ture for DHCP , False for static config.

// Static network config, only relevant if dhcp=false
const IPAddress ip(192, 168, 1, 5);
const IPAddress gateway(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

int Pin = 13; // GPIO13
WiFiServer server(80);

int count = 0;
  
void setup() {

  pinMode(Pin, OUTPUT);
  digitalWrite(Pin, LOW);
  
  WiFi.hostname("PiDoorIntercomGong");
  WiFi.mode(WIFI_STA);
  WiFi.softAPdisconnect(true);
  
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  if (dhcp) {
    Serial.println("With DHCP");
  }else{
    Serial.print("With Static IP: ");
    Serial.println(ip);
    WiFi.config(ip, gateway, subnet);
  }
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {

  WiFiClient client = server.available();

  if (!client) {
    // Check if a client has connected
    digitalWrite(Pin, LOW);
    delay(10);
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    digitalWrite(Pin, LOW);
    delay(10);
    count++;
    if(count>100)
    {
      Serial.println("client timeout");
      count=0;
      return;
    }
  }

  String request = client.readStringUntil('\r');
  Serial.println("New Request");
  delay(1);
  client.flush();

  // Directly Respond with no Content
  client.println("HTTP/1.1 204 no content");
  client.println(""); //  do not forget this one

  //only ring on /gong to prevent scanners/network analyzers in network to trigger
  if (request.indexOf("/gong") != -1)  {
    digitalWrite(Pin, HIGH);
    delay(100);
    digitalWrite(Pin, LOW);
  }

  delay(1);
  Serial.println("Request Finished");
  Serial.println("");
  
}
