#include "Arduino.h"
#include "JoyStick.h"

JoyStick::JoyStick(int xPin, int yPin, int bPin) {
  this->xPin = xPin;
  this->yPin = yPin;
  this->bPin = bPin;

  pinMode(this->xPin, INPUT);
  pinMode(this->yPin, INPUT);
  pinMode(this->bPin, INPUT_PULLUP);
}

int JoyStick::getX() {
  return analogRead(this->xPin);
}

int JoyStick::getY() {
  return analogRead(this->yPin);
}

bool JoyStick::isButtonDown() {
  return digitalRead(this->bPin) == 0;
}