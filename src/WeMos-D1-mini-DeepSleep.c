
/* Arduino Board selected: LOLIN(WeMos) D1 R2 & Mini board model */

#include <Arduino.h>
#include <ESP8266WiFi.h>   

// Add your own static IP address and gateway here - DHCP wastes powerstatic IP saves
IPAddress ip(nnn,nnn,nnn,nnn); 
IPAddress gateway(nnn,nnn,nnn,nnn);
IPAddress subnet(255, 255, 255, 0);
const char* ssid     = "yourSSID";     
const char* password = ""; // Use unsecured WiFi on isolated subnet to save power -

const int sleepSeconds = 60;  // My test sleep duration
 
void setup() {
  WiFi.mode(WIFI_OFF); // Start with no radio to avoid spike in voltage consumption
  WiFi.forceSleepBegin(); // Need to do this regardless of WiFi.mode
  delay(1); // Required settle time

  // Serial monitor output Only used for demo in this template
  Serial.begin(115200);  
  Serial.println("\n\nWake up");

  // Connect D0 to RST for this wake up call
  pinMode(D0, WAKEUP_PULLUP);

  WiFi.forceSleepWake(); // Start the radio
  delay(1);  // Required settle time
  WiFi.persistent( false );  // Disable usage of last config used 
  
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password); // Connect to the network
  WiFi.softAPdisconnect (true); // switch off AP mode
  
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  // Add your code here for activity during active WiFi connection
  delay(3); // This delay for demo only

  WiFi.disconnect(true);
  delay(1); // Required settle time

  Serial.println("Sleeping...");

  /* 
    WAKE_RF_DISABLED keeps radio disabled on next wakeup
    Force deep sleep - in microseconds
  */
  ESP.deepSleep( (sleepSeconds * 2000000), WAKE_RF_DISABLED );
}
 
void loop() {
 }
