// Master
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11);
// sensor
const int linePin = 8;
int value;
//
void setup()
{
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(linePin, INPUT);
}

void loop()
{
  value = digitalRead(linePin);
  Serial.println(value);
  BTSerial.println(value);
  delay(1000);
}