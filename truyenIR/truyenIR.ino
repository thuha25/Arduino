#include <Arduino.h>
#include <IRremote.hpp>
#define IR_SEND_PIN 3
#define line 4
#define light_pin 5
#define gas_pin A0
const int trigPin = 8;
const int echoPin = 9;
long duration;
int distance;
int vrx, vry;
#include "DHT.h"       
#define DHTPin 6    
#define DHTType DHT22
DHT HT(DHTPin, DHTType);

void setup() {
  float humidity = HT.readHumidity(); 
  float temperaturec = HT.readTemperature( );
  float temperatureF = HT.readTemperature(true);
  Serial.begin(9600);
  IrSender.begin(IR_SEND_PIN);
  pinMode(line, INPUT);
  pinMode(gas_pin, INPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  HT.begin();
}

uint16_t address = 0x3A13;
uint8_t command = 0x1;
int_fast8_t repeats = 0;

void loop() {
  int value = digitalRead(line);
  int gas = analogRead(gas_pin);
  int light = analogRead(light_pin);
  float humidity = HT.readHumidity(); 
  float temperaturec = HT.readTemperature( );
  float temperatureF = HT.readTemperature(true);

  // Serial.println(value);
  // Serial.println(gas);
  // if (value == 0) {
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else {
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }
  // digitalWrite(trigPin, LOW);
  // delayMicroseconds(2);
  // digitalWrite(trigPin, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(trigPin, LOW);
  // duration = pulseIn(echoPin,HIGH);
  // distance = duration * 0.034/2;
  // Serial.println(distance);
  // if (distance > 10 && distance < 20) {
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else {
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }

  // if (gas > 200) {
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else {
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }

  // Serial.println(light);
  // if (light > 700) {
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else {
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }

  // Serial.print("Humidity : ");
  // Serial.print(humidity);
  // Serial.print(", Temperature: ");
  // Serial.print(temperaturec);
  // Serial.print("oC ~ ");
  // Serial.print(temperatureF);
  // Serial.println("oF");
  // if (humidity > 30) {
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else {
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }

  // vrx = analogRead(A0);
  // vry = analogRead(A1);
  // Serial.print("x: ");
  // Serial.print(vrx);
  // Serial.print(", y: ");
  // Serial.print(vry);
  // Serial.println();
  // if (vrx <= 200) {
  //   // Gạt xuống => Thuận chiều
  //   IrSender.sendNEC(address, 0x0, repeats);
  // } else if (vrx >= 800) {
  //   // Gạt lên => Ngược chiều
  //   IrSender.sendNEC(address, 0x1, repeats);
  // }
  // if (vry <= 200) {
  //   // Gạt trái: Nhanh dần
  //    IrSender.sendNEC(address, 0x2, repeats);
  // } else if (vry >= 800) {
  //   // Gạt phải: Chậm dần
  //   IrSender.sendNEC(address, 0x3, repeats);
  // }
  delay(200);
}