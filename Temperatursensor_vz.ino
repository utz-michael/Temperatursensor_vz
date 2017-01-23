

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define URL "/middleware.php/data/d49922e0-e14c-11e6-9e4a-f94a5f8e4914.json?operation=add&value="

// Data wire is plugged into port 0 on the Arduino
#define ONE_WIRE_BUS 0

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Wlan-Daten: Name des Netzwerks (SSID) und Passwort
#define SSID "Connection1"

byte servervolk[]  = { 192, 168, 192, 105 };//Volkszähler server schreiben
int PERIOD=1;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
  Serial.print(".");
  }
  Serial.println("WiFi connected");
  delay(5000);
Serial.println(WiFi.localIP());
  // Start up the library
  sensors.begin();
}
void loop()
{
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0); 
 Serial.print(tempC);
 Serial.println(" C");
  if (client.connect(servervolk, 80)) {
    Serial.println("Connectet to 192.168.192.105");
    String cmd = "GET ";
    cmd += URL;
    cmd += tempC;
    cmd += " HTTP/1.1";
     Serial.println(cmd);
     client.println(cmd);
     client.println("Host: 192.168.192.105");
     client.println("Connection: close");
     client.println();
     delay(2000);
    if (client.available()) {
    char c = client.read();
    Serial.println(c);
    }       
    client.stop();
    Serial.println("Connection closed");
  }
  else {
    Serial.println("Connection failed");
  }
    Serial.println(" 30 Sekunden Deep Sleep");
    ESP.deepSleep(300 * 1000000); // 300 secs
    delay(100);
    Serial.println(" fertig ");
   //delay(PERIOD * 60000); 
}

