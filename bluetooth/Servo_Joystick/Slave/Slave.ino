int command;
// servo
#include <Servo.h>
#include "SoftwareSerial.h"
#include <Arduino_FreeRTOS.h>
SoftwareSerial BTSerial(10, 11);
const int servo_pin = 8;
Servo servo;
int degree = 90;
int servo_count_delay = 0;
int servo_max_delay = 100;
void servoSpin() {
  while (true) {
    servo.write(degree);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
    servo.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS);  // delay 1 second
  }
}
void setup() {
  Serial.begin(19200);
  BTSerial.begin(9600);
  servo.attach(servo_pin);
  xTaskCreate(servoSpin, "servoSpin", 512, NULL, 1, NULL);
}

void loop() {
   if (BTSerial.available()) {
    command = BTSerial.read();
    Serial.println(command);
    if (command == '0') {
      degree = 45;
    } else if (command == '1') {
      degree = 90;
    } else if (command == '2') {
      degree = 135;
    } else if (command == '3') {
      degree = 180;
    }
  }
  delay(10);
}


