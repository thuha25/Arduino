// Master
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
// sensor
#include <DHT.h>
const int dht11_pin = 8;
const int dht_model = DHT11;
float humidity;
float temperature;
DHT dht11(dht11_pin, dht_model);
//
void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  dht11.begin();
}

void loop() {
  humidity = dht11.readHumidity();
  temperature = dht11.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Không có giá trị!");
  } else {
    Serial.print("Độ ẩm: ");
    Serial.print(humidity);

    Serial.print("%; Nhiêt độ: ");
    Serial.print(temperature);
    Serial.println("\u2103");
  }
  if (temperature <= 27) {
    BTSerial.write('0');
  } else {
    BTSerial.write('1');
  }
  delay(50);
}
