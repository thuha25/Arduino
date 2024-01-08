// #include <SoftwareSerial.h>
// SoftwareSerial BTSerial(10, 11);

// void setup() {
//   Serial.begin(9600);
//   Serial.println("Serial 9600 is ready");

//   BTSerial.begin(38400);
// }

// void loop() {
//   if(BTSerial.available())
//     Serial.write(BTSerial.read());
//   if(Serial.available())
//     BTSerial.write(Serial.read());
// }

// #include <SoftwareSerial.h>
// #include <Stepper.h>
// SoftwareSerial BTSerial(10,11);
// const int STEPS = 2048; // Số bước trong một vòng
// Stepper myStepper = Stepper(STEPS, 6, 8, 7, 9);
// int degreeToSteps(int degree, int STEPS = 2048)
// {
//     if (degree == 0)
//         return 0;
//     return STEPS / (360 / degree);
// }
// void setup(){
//   Serial.begin(9600);
//   BTSerial.begin(9600);
//   myStepper.setSpeed(14);
// }
// char c;
// void loop(){
//   while(BTSerial.available()){
//     c = BTSerial.read();
//     Serial.println(c);
//     delay(5);
//   }
//   // while(Serial.available()){
//   //   char c = Serial.read();
//   //   BTSerial.write(c);
//   //   delay(5);
//   // }
//   if(c == '1') {
//       int degreeC = degreeToSteps(45); // quay 45 độ mỗi 1 lần bước(quay)
//       myStepper.step(degreeC);
//       delay(200);
//     } else {
//       int degreeC = degreeToSteps(-45); // quay 45 độ mỗi 1 lần bước(quay)
//       myStepper.step(degreeC);
//       delay(200);
//     }
// }
#include <SoftwareSerial.h>
#include <Servo.h>
int servoPin = 9;
Servo servo;

SoftwareSerial BTSerial(10, 11);

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(9600);
  servo.attach(servoPin);
}
char c;
void loop()
{
  while (BTSerial.available())
  {
    c = BTSerial.read();
    Serial.println(c);
    delay(5);
  }
  // float dist = c.toFloat();
  if (c == '1')
  {
    servo.write(45);
    delay(1000);
    servo.write(0);
  }
  else
  {
    servo.write(180);
    delay(1000);
    servo.write(0);
  }
}