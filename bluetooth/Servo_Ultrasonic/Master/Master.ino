// Master
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,3);
// sensor
const int trigger_pin = 9;
const int pw_pin = 8;
const int trigger_delay = 10;
long duration;
float cm;
//
void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);
  pinMode(pw_pin, INPUT);
}

void loop() {
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(trigger_delay);
  digitalWrite(trigger_pin, LOW);
  duration = pulseIn(pw_pin, HIGH);
  cm = duration * 0.017;
  Serial.print(cm);
  Serial.println(" cm");
  if (cm <= 12.5) {
    BTSerial.write('0');
  } else {
    BTSerial.write('1');
  }
  delay(500);
}