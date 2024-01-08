#include "MyServo.h"
#include "Arduino.h"
#ifdef ARDUINO_UNO
#include <Arduino_FreeRTOS.h>
#endif

Servo servo;
int servoAngle = 45;
bool isSwinging = false;

void servoAttach(int pin) {
  servo.attach(pin);
  pinMode(pin, OUTPUT);
}
void setAngle(int angle) {
  servoAngle = angle;
}
void startSwinging() {
  isSwinging = true;
}
void stopSwinging() {
  isSwinging = false;
}

void swing() {
  servo.write(servoAngle);
  Serial.println(servoAngle);
  delay(500);
  servo.write(0);
  Serial.println(0);
  delay(500);
}

void servoTask(void* parameter) {
  while (1) {
    // Serial.print("");
    if (isSwinging) {
      // Serial.println(servoAngle);
      servo.write(servoAngle);
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    servo.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setupServo() {
  xTaskCreate(servoTask, "servoTask", 512, NULL, 0, NULL);
}