#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Mimi_CellSpot_2.4GHz";
const char* pass = "narrowpiano471";

ESP8266WebServer server(80);

Servo myservo;

void setup(void){
  Serial.begin(9600);
  Serial.println("");
  
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", [](){
    server.send(200, "text/plain", "Open /servo?value=90 to control servo");
  });

  server.on("/servo", [](){
    String sval = server.arg("value");
    int ival = sval.toInt();
    Serial.print("Servo: ");
    Serial.println(ival);
    myservo.write(ival);
    server.send(200, "text/plain", String(ival, DEC));
  });

  server.begin();
  Serial.println("HTTP server started");
  
  myservo.attach(4);   // GPIO2
  myservo.write(0);
}
 
void loop(void){
  server.handleClient();
} 
