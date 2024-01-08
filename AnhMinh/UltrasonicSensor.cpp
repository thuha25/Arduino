#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasnonicSensor::UltrasnonicSensor(int triggerPin, int echoPin) {
  this->trigPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

int UltrasnonicSensor::readDuration() {
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration;
}

int UltrasnonicSensor::readDistance() {
  int duration = this->readDuration();
  return duration * 0.034 / 2;
}