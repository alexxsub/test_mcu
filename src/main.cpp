#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 12

#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


float Temperature;
float Humidity;




void setup() {
  Serial.begin(115200);
  pinMode(DHTPIN, INPUT);
  dht.begin();
}

void loop() {
   Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temperature = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.print(F("°C "));
  delay(1000);
}