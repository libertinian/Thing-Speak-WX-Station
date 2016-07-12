# ThingSpeak WX Station
ThingSpeak-integrated weather station using Arduino MKR1000 and Adafruit BME280 temperature, humidity, and pressure sensor.

This sketch is the amalgation of the Arduino tutorial for using WiFi 101 ThingSpeak Data Uploader (http://arduino.cc/en/Tutorial/WiFi101ThingSpeakDataUploader) and the Adafruit example sketch for the BME280 breakout board (http://www.adafruit.com/products/2650). 

This has been tested on a Arduino MKR1000.

##Quick and Dirty Wiring Diagram 

  *MKR1000 to BME280*
- VCC to 3Vo
- GND to GND
- 13  to SCK
- 12 to SDO
- 11 to SDI
- 10 to CS

##To Do List
- [ ] Implement a method to gather sea-level pressure data based on user-supplier location to improve apparent altitude measurements.
- [ ] Implement a better method to use GPS to determine sea level pressure at coordinates.
- [ ] Local historical data tracking
