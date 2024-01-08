// Master
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);
// sensor
#include <DHT.h>
const int dht_pin = 8;
const int dht_model = DHT22;
float humidity;
float temperature;
DHT dht(dht_pin, dht_model);
//
void setup()
{
  BTSerial.begin(9600);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature))
  {
    Serial.println("Không có giá trị!");
  }
  else
  {
    Serial.print("Độ ẩm: ");
    Serial.print(humidity);

    Serial.print("%; Nhiêt độ: ");
    Serial.print(temperature);
    Serial.println("\u2103");
  }
  if (temperature <= 31)
  {
    BTSerial.write('0');
  }
  else
  {
    BTSerial.write('1');
  }
  delay(1000);
}
