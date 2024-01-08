const int ledPin = 13;
const int buzzlePin = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzlePin, OUTPUT);
}

void loop()
{
  int val = analogRead(A1);
  float temp = val * 500.0 / 1023.0;
  Serial.println(temp);
  if (temp > 27.0)
  {
    for (int x = 0; x < 180; x++)
    {
      float val = (sin(x * (3.1412 / 180.0)));
      float toneVal = 2000 + int(val * 1000);
      tone(buzzlePin, toneVal);
      delay(2);
    }
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    noTone(buzzlePin);
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}