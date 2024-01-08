#include <IRremote.hpp>
int pin=7, value=0;
boolean i = 0;
void setup()
{
  Serial.begin(9600);
  IrSender.begin(3);
  pinMode(pin,INPUT);
}
void loop() 
{
  int val = digitalRead(pin);
  Serial.println(val);
  IrSender.sendNECRaw(val);
  delay(500);
}