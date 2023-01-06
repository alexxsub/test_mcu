#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
unsigned long delayTime;

#define DHTPIN 12

#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


float Temperature;
float Humidity;




void setup() {
  Serial.begin(115200);
  pinMode(DHTPIN, INPUT);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.75);
  display.setTextColor(WHITE);
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

  display.setCursor(0,0);
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(Temperature);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(Humidity);
  display.print(" %");
  
  display.display();
  
  delay(1000);
}
