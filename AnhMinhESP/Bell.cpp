#include "HardwareSerial.h"
#include "Arduino.h"
#ifdef ARDUINO_UNO
#include <Arduino_FreeRTOS.h>
#endif
#include "Bell.h"

Bell::Bell(int pin) {
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  Bell::beginTask(this);
}

void Bell::beginTask(Bell *bell) {
  xTaskCreate(Bell::bellTask, "bellTask", 128, (void*) bell, 0, NULL);
}

void Bell::bellTask(void *parameter) {
  Bell* bell = (Bell*) parameter;
  int x = 0;
  while(1) {
    x = (x + 1) % 181;
    if(bell->isOn) {
      int val = 1000 * sin(x * 3.14 / 180);
      bell->bellTone(val);
    } else {
      bell->bellNoTone();
    }
    delay(2);
  }
}

void Bell::turnOn() {
  this->isOn = true;
}

void Bell::turnOff() {
  this->isOn = false;
}

void Bell::bellTone(int val) {
  tone(this->pin, val);
}

void Bell::bellNoTone() {
  noTone(this->pin);
}