// #include "BlenDArd.h"
// LightSensor lightsensor(A0);
// DCMotor dc(9, 6);
// JoyStick joystick(A0,A1,7);
// void setup() {
//   Serial.begin(9600);
// }
// // int value;
// int x,y,z;
// bool isClockwise = false;

// void loop() {
//   x = joystick.getX();
//   y = joystick.getY();
//   z = joystick.isButtonDown();
//   Serial.print(x);
//   Serial.print(" ");
//   Serial.print(x);
//   Serial.print(" ");
//   Serial.println(z);
//   if(x < 100){
//     isClockwise = false;
//   }else if(x > 600){
//     isClockwise = true;
//   }
//   if(y < 100) {
//     dc.setSpeed(100);
//   }else if(y>600){
//     dc.setSpeed(200);
//   }
//   if(joystick.isButtonDown()) {
//     dc.setSpeed(0);
//   }
//   if(isClockwise)
//     dc.rotateClockwise();
//   else
//     dc.rotateCounterClockwise();
//   // value = lightsensor.read();
//   // Serial.println(value);
//   // if (value > 700) {
//   //   dc.rotateCounterClockwise();
//   //   //nguoc chieu kim
//   // }else{
//   //   dc.rotateClockwise();
//   //   // cung chieu kim
//   // }
// }

//

// #include "BlenDArd.h"
// // LineSensor sensor(3);
// // LightSensor light(0);
// Led led(13);
// UltrasnonicSensor sensor(4, 5);
// Bell bell(6);
// JoyStick joystick(A0,A1,7);
// void setup() {
//   Serial.begin(9600);
//   delay(1000);
// }

// void loop() {
//   // int val = sensor.read();
//   // int val = light.read();
//   int val = sensor.readDistance();
//   // Serial.println(val);

//   int x = joystick.getX();
//   int y = joystick.getY();
//   bool z = joystick.isButtonDown();

//   Serial.print(x);
//   Serial.print(" ");
//   Serial.print(y);
//   Serial.print(" ");
//   Serial.println(z);
//   // if(val == 0){
//   //   led.turnOn();
//   // } else {
//   //   led.turnOff();
//   // }
//   // if(val > 10 && val < 20) {
//   //   led.turnOn();
//   //   bell.turnOn();
//   // } else {
//   //   led.turnOff();
//   //   bell.turnOff();
//   // }
//   delay(100);
// }

// #include "BlenDArd.h"
// LightSensor sensor(A0);
// // do:vcc, nau:gnd
// void setup() {
//   Serial.begin(9600);
//   servoAttach(9);
//   // startSwinging();
//   setupServo();
//   setAngle(90);
// }

// void loop() {
//   int val = sensor.read();
//   Serial.println(val);
//   if(val > 700) {
//     startSwinging();
//   } else {
//     stopSwinging();
//   }
//   delay(200);
// }

// #include <Stepper.h>
// #include "BlenDArd.h"
// LightSensor sensor(A0);
// const int STEPS = 2048; // Số bước trong một vòng
// Stepper myStepper = Stepper(STEPS, 8, 10, 9, 11);
// int degreeToSteps(int degree, int STEPS = 2048)
// {
//     if (degree == 0)
//         return 0;
//     return STEPS / (360 / degree);
// }

// void setup()
// {
//     Serial.begin(9600);
//     myStepper.setSpeed(14); // 14 RPM - Rotations per minute
// }
// void loop()
// {
//     int val = sensor.read();
//     Serial.println(val);
//     if (val > 700)
//     {
//         myStepper.setSpeed(14);          // 18 RPM - Rotations per minute
//         int degreeC = degreeToSteps(45);
//         myStepper.step(degreeC);         // quay thuan chiều kim đồng hồ
//         delay(200);
//     }
//     else
//     {
//         myStepper.setSpeed(14); // 14 RPM - Rotations per minute
//         int degreeCC = degreeToSteps(90);
//         myStepper.step(-degreeCC); // quay nguoc chiều kim đồng hồ - quay 1 vòng
//         delay(200);
//     }
// }
