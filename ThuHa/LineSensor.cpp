#include "Arduino.h"
#include "LineSensor.h"

LineSensor::LineSensor(int pin) {
  this->pin = pin;
  pinMode(this->pin, INPUT);
}

int LineSensor::read() {
  return digitalRead(this->pin);
}