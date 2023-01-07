#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <EasyButton.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);



#define DHTPIN 12
#define BTNPIN 14

#define DHTTYPE DHT11
#define BAUDRATE 115200

DHT dht(DHTPIN, DHTTYPE);
EasyButton button(BTNPIN);

float Temperature;
float Humidity;

long timing=0;

String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}

void onPressed()
{
  Serial.println("Button pressed");
}
void onSequenceMatched()
{
  Serial.println("Button pressed 3 times");
}
void buttonPressedTwoSeconds()
 {
  Serial.println("Button pressed for 2 sec");
}
void print_screen(){
  display.setCursor(0,0);
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print(utf8rus("Температура: "));
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
  display.print(utf8rus("Влажность: "));
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(Humidity);
  display.print(" %");
  
  display.display();
  

}
void setup() {
  Serial.begin(BAUDRATE);
  pinMode(DHTPIN, INPUT);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1.75);
  display.setTextColor(WHITE);
  
  button.begin();
  button.onPressed(onPressed);
  button.onPressedFor(2000, buttonPressedTwoSeconds);
  button.onSequence(3 /* number of presses */, 2000 /* timeout */, onSequenceMatched /* callback */);
}
void print_serial()
{
   Serial.print(F("Humidity: "));
  Serial.print(Humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(Temperature);
  Serial.println(F("°C "));
}
void read_sensor(){
     Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  Temperature = dht.readTemperature();


  // Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(Temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

}
void loop() {

 

 
if (millis() - timing < 1000){ 
  button.read();
} else{
  read_sensor();
  print_serial();
  print_screen();
  timing = millis(); 
  
 }

 // delay(1000);
}
