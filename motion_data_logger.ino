#include "ultrasonic_sensor.h"
#include "sd_card.h"
#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_Sensor.h>

using namespace std;

File file;

//Constants
#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

void setup() {
  Serial.begin(9600);
  dht.begin();

  setup_sensor();
  setupSDCard();

  file = createFile("TestData.csv");
  writeNewLineToFile(file, "millis,stamp,distance,temp,hum");
}

void loop() {
  delayLogs();

  double distance = getMetersdistance();
  float humdity = dht.readHumidity();
  float temperature = dht.readTemperature();

  writeNewLineToFile(file, getTimestamp() + "," + String(distance) + "," + String(temperature) + "," + String(humdity));

  if (isSynced()) return;
}


