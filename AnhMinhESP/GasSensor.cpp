#include "Arduino.h"
#include "GasSensor.h"

GasSensor::GasSensor(int analogPin) {
  this->pin = analogPin;
}

int GasSensor::read() {
  return analogRead(this->pin);
}