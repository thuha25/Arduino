#include <DHT.h>
#include <DHT_U.h>

#include <Servo.h>
// #define line_pin 4
// #define trigPin 5
// #define echoPin 4
#define micPin A0
int servoPin = 9;
Servo servo;


int potpin = 0;
int val;
void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  // pinMode(line_pin, INPUT);
  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
}

void loop() {
  float mx = 0;
  for(int i = 0; i < 100; i++) {
    float val = analogRead(micPin);
    mx = max(val, mx);
    // mn = min(val, mn);
    delay(1);
  }

  Serial.println(mx);
  
  if(mx>80) {
    servo.write(45);
    delay(1000);
    servo.write(0);
  } else {
    servo.write(100);
    delay(1000);
    servo.write(0);
  }
  delay(1000); 
}
