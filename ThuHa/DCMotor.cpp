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
  analogWrite(this->in2, 0);
}

void DCMotor::rotateCounterClockwise() {
  analogWrite(this->in1, 0);
  analogWrite(this->in2, speed);
}