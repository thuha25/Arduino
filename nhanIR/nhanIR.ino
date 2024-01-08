#include <Servo.h>
#include <Arduino_FreeRTOS.h>
#include <IRremote.hpp>
#include <Stepper.h>
const int servoPin = 9;

Servo servo_9;

const int IR_RECEIVE_PIN = 2;

const int STEPS = 2048; // Số bước trong một vòng
Stepper myStepper = Stepper(STEPS, 8, 10, 9, 11);
int degreeToSteps(int degree, int STEPS = 2048)
{
  if (degree == 0)
    return 0;
  return STEPS / (360 / degree);
}

int in1 = 9;
int in2 = 10;
int speed = 250;

void setup()
{
  Serial.begin(19200);
  IrReceiver.begin(IR_RECEIVE_PIN);
  servo_9.attach(9);
  xTaskCreate(servoSpin, "servoSpin", 256, NULL, 1, NULL);
  myStepper.setSpeed(14);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

int degree = 90;
void servoSpin()
{
  while (true)
  {
    servo_9.write(degree);
    vTaskDelay(500 / portTICK_PERIOD_MS); // delay 1 second
    servo_9.write(0);
    vTaskDelay(500 / portTICK_PERIOD_MS); // delay 1 second
  }
}

void loop()
{
  if (IrReceiver.decode())
  {
    uint16_t address = IrReceiver.decodedIRData.address;
    // Serial.print("address: ");
    // Serial.println(address);
    if (address == 0x3A13)
    {
      uint8_t command = IrReceiver.decodedIRData.command;
      Serial.print("command: ");
      Serial.println(command);
      if (command == 0x0)
      {
        // servo:
        degree = 180;
        // stepper:
        //  myStepper.setSpeed(14);          // 18 RPM - Rotations per minute
        //  int degreeC = degreeToSteps(45); // quay 180 độ mỗi 1 lần bước(quay)
        //  myStepper.step(degreeC);         // quay thuan chiều kim đồng hồ
        // dc
        //  analogWrite(in1, speed);
        //  digitalWrite(in2, LOW);
      }
      else
      {
        // servo:
        degree = 90;
        // stepper
        //  myStepper.setSpeed(14); // 14 RPM - Rotations per minute
        //  int degreeCC = degreeToSteps(45);
        //  myStepper.step(-degreeCC); // quay nguoc chiều kim đồng hồ - quay 1 vòng
        // dc
        //  digitalWrite(in1, LOW);
        //  analogWrite(in2, speed);
      }
    }
    IrReceiver.resume();
  }
}