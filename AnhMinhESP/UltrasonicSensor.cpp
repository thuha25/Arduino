#include "Arduino.h"
#include "UltrasonicSensor.h"

UltrasnonicSensor::UltrasnonicSensor(int triggerPin, int echoPin) {
  this->trigPin = triggerPin;
  this->echoPin = echoPin;
  pinMode(this->trigPin, OUTPUT);
  pinMode(this->echoPin, INPUT);
}

void UltrasnonicSensor::trigger() {
  digitalWrite(this->trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(this->trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  float distance = (float) duration * 0.034 / 2;
  this->duration = duration;
  this->distance = distance;
}

int UltrasnonicSensor::readDuration() {
  return this->duration;
}

int UltrasnonicSensor::readDistance() {
  return this->distance;
}