// Gọi thư viện DHT11
#include "DHT.h"
#define DHTPin 4
#define DHTType DHT11
#define BellPin 11

DHT HT(DHTPin, DHTType);

void setup()
{
  pinMode(BellPin, OUTPUT);
  Serial.begin(9600);
  HT.begin();
  delay(1000);
}

int x = 0;

void loop()
{
  float humidity = HT.readHumidity();
  float temperaturec = HT.readTemperature();
  float temperatureF = HT.readTemperature(true);

  x = (x + 1) % 180;
  int val = 1000 * sin(x);

  if (humidity > 70 && temperaturec > 25)
  {
    tone(BellPin, val);
  }
  else
  {
    noTone(BellPin);
  }

  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.print(", Temperature: ");
  Serial.print(temperaturec);
  Serial.print("oC ~ ");
  Serial.print(temperatureF);
  Serial.println("oF");
  delay(100);
}