#include "Arduino.h"
#include "LightSensor.h"

LightSensor::LightSensor(int analogPin) {
  this->pin = analogPin;
}

int LightSensor::read() {
  return analogRead(this->pin);
}