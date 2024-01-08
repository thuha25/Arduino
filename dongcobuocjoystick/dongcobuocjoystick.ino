#include <Stepper.h>
const int vx = A0;
const int vy = A1;
const int sw = 7;
const int STEPS = 2048; // Số bước trong một vòng
Stepper myStepper = Stepper(STEPS, 8, 10, 9, 11);
int degreeToSteps(int degree, int STEPS = 2048)
{
  if (degree == 0)
    return 0;
  return STEPS / (360 / degree);
}
void setup()
{
  pinMode(sw, INPUT_PULLUP); // neu chi la INPUT thi phai mac dien tro
  pinMode(vx, INPUT);
  pinMode(vy, INPUT);
  Serial.begin(9600);
}
void loop()
{
  int x = analogRead(vx);
  int y = analogRead(vy);
  int s = digitalRead(sw); // HIGH neu khong bam, LOW neu bam
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("Y = ");
  Serial.print(y);
  Serial.print("S = ");
  Serial.println(s);
  if (x > 600 && s == 1)
  {
    myStepper.setSpeed(14);          // 18 RPM - Rotations per minute
    int degreeC = degreeToSteps(60); // quay 180 độ mỗi 1 lần bước(quay)
    myStepper.step(-degreeC);        // quay ngược chiều kim đồng hồ
    delay(200);
  }
  else if (x < 400 && s == 1)
  {
    myStepper.setSpeed(14); // 14 RPM - Rotations per minute
    int degreeCC = degreeToSteps(60);
    myStepper.step(degreeCC); // quay cùng chiều kim đồng hồ - quay 1 vòng
    delay(200);
  }
  else if (s == 0)
  {
    Serial.println("OK");
    delay(200);
    myStepper.setSpeed(0); // 14 RPM - Rotations per minute
    myStepper.step(0);
  }
}
