# ThingSpeak WX Station
ThingSpeak-integrated weather station using Arduino MKR1000 and Adafruit BME280 temperature, humidity, and pressure sensor.

This sketch is the amalgation of the Arduino tutorial for using WiFi 101 ThingSpeak Data Uploader (http://arduino.cc/en/Tutorial/WiFi101ThingSpeakDataUploader) and the Adafruit example sketch for the BME280 breakout board (http://www.adafruit.com/products/2650). 

This has been tested on a Arduino MKR1000.

Currently working on implementing a method to gather sea-level pressure data based on location to improve apparent altitude measurements.

Quick and Dirty Wiring
       Diagram
-----------------------
| MKR1000  |   BME280 |
|   Pin    |    Pin   |
-----------------------
|   VCC ------> 3Vo   |
|   GND ------> GND   |
|   13  ------> SCK   |
|   12  ------> SDO   |
|   11  ------> SDI   |
|   10  ------> CS    |
----------------------
