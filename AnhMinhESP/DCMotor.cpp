#include "Arduino.h"
#include "DCMotor.h"

DCMotor::DCMotor(int in1, int in2) {
  this->in1 = in1;
  this->in2 = in2;
  pinMode(this->in1, OUTPUT);
  pinMode(this->in2, OUTPUT);
}

void DCMotor::setSpeed(int speed) {
  this->speed = speed;
}

void DCMotor::rotateClockwise() {
  analogWrite(this->in1, speed);
  digitalWrite(this->in2, LOW);
}

void DCMotor::rotateCounterClockwise() {
  digitalWrite(this->in1, LOW);
  analogWrite(this->in2, speed);
}