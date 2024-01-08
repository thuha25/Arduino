#include <Stepper.h>
float temperature;
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
    // pinMode(DHTPin, INPUT);
    // pinMode(echoPin, INPUT);
    HT.begin();
    Serial.begin(9600);
    myStepper.setSpeed(14); // 14 RPM - Rotations per minute
}

void loop()
{
    // digitalWrite(trigPin, LOW);
    // delayMicroseconds(2);
    // digitalWrite(trigPin, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(trigPin, LOW);
    // long duration = pulseIn(echoPin, HIGH);
    // float distance = duration * 0.034 / 2;
    // Serial.print("khoang cach: ");
    // Serial.print(distance);
    // Serial.println(" cm");
    // delay(1000);
    temperature = HT.readTemperature();
    Serial.println(temperature);
    if (temperature < 29)
    {
        myStepper.setSpeed(14);          // 18 RPM - Rotations per minute
        int degreeC = degreeToSteps(45); // quay 180 độ mỗi 1 lần bước(quay)
        myStepper.step(degreeC);         // quay thuan chiều kim đồng hồ
        delay(200);
    }
    else
    {
        myStepper.setSpeed(14); // 14 RPM - Rotations per minute
        int degreeCC = degreeToSteps(45);
        myStepper.step(-degreeCC); // quay nguoc chiều kim đồng hồ - quay 1 vòng
        delay(200);
    }
}
