int led = 13, pin = 7, value = 0;
// void setup(){
//   pinMode(led,OUTPUT);
//   pinMode(pin,INPUT);
//   digitalWrite(led,LOW);
// }
// void loop(){
//   value = digitalRead(pin);
//   digitalWrite(led,value);
// }

// nhấn nhả nút
boolean i = 0;
void setup()
{
  pinMode(pin, INPUT);
  pinMode(led, OUTPUT);
}
void loop()
{
  if (digitalRead(pin) == HIGH)
  {
    i = !i;
    while (digitalRead(pin) == HIGH)
      ;
    delay(200);
  }
  if (i == 1)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}