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
