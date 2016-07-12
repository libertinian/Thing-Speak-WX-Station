/*
Amalgamation of the Arduino tutorial for WiFi 101 connections to ThingSpeak and the BME280 sensor example sketch.
Please see README for more details.
Amalgamated by Libertinian on 7/10/16
* /


#include <SPI.h>
#include <WiFi101.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


// Local Network Settings
char ssid[] = "<INSERT YOUR SSID HERE>";     //  your network SSID (name)
char pass[] = "<INSERT YOUR WPA PASSWORD HERE>";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String APIKey = "<INSERT YOUR THINGSPEAK WRITE API KEY HERE>";             // enter your channel's Write API Key
const int updateThingSpeakInterval = 60 * 1000; // 60 second interval at which to update ThingSpeak

// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;

// Initialize Arduino Ethernet Client
WiFiClient client;

//SETUP WX STATION (BME280)
const bool showFahrenheit = true; // Chnage to false for Celsius
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

void setup() {
  // Start Serial for debugging on the Serial Monitor
  Serial.begin(115200);


  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print(F("Attempting to connect to SSID: "));
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();

  //SETUP BME280
  Serial.print(F("Checking for WX station (BME280)..."));

  if (!bme.begin()) {
    Serial.println(F("FAIL!!! Could not find a valid BME280 sensor, check wiring!"));
    while (1);
  }

  Serial.println(F("SUCCESS!!!"));
  Serial.println();
  Serial.println(F("Starting weather station operations..."));
  Serial.println();
}

void loop() {
  // read values from pins and store as strings


  String light = String(analogRead(A0), DEC); // read light value

  // find temp value

  float temp = bme.readTemperature();                       //read temperature in Celsius
  if (showFahrenheit) {                                 //Convert Celsius to Fahrenheit
    temp = temp * 1.8 + 32;
  }
  String tempString = "field1=" + String(temp);
  int bar = (bme.readPressure() / 100.0);                  //read barometric pressure in hPa
  String barString = "&field2=" + String(bar);

  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);  //get approx. altitude in meters based on barometric pressure.
  String altString = "&field3=" + String(altitude);

  int hum = bme.readHumidity();                           //get percent humidity
  String humString = "&field4=" + String(hum);


  String thingString = String(tempString + barString + altString + humString);

  // Print Update Response to Serial Monitor
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected) {
    Serial.println("...disconnected");
    Serial.println();
    client.stop();
  }
  // Update ThingSpeak
  if (!client.connected() && (millis() - lastConnectionTime > updateThingSpeakInterval)) {
    updateThingSpeak(thingString);
    /* Serial.println(temp);
       Serial.println(bar);
       Serial.println(altitude);
       Serial.println(hum);
    */
  }
  lastConnected = client.connected();
}

void updateThingSpeak(String tsData) {
  if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + APIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    lastConnectionTime = millis();
    Serial.print("TSData --- ");
    Serial.println(tsData);
    if (client.connected()) {
      Serial.println(F("Connecting to ThingSpeak..."));
      Serial.println();
    }
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(F("signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}
