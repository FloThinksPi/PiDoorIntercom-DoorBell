#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "password";

int Pin = 13; // GPIO13
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(Pin, OUTPUT);
  digitalWrite(Pin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

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
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    digitalWrite(Pin, LOW); // To Prevent odd Triggers overtime, it somehow works ;)
    delay(1);
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    digitalWrite(Pin, LOW); // To Prevent odd Triggers overtime, it somehow works ;)
    delay(1);
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
