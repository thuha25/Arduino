int led = 13;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  while (Serial.available() == 0)
  {
  }
  String c = Serial.readString();
  c.trim();
  if (c == "ON")
    digitalWrite(led, HIGH);
  else if (c == "OFF")
    digitalWrite(led, LOW);
}
