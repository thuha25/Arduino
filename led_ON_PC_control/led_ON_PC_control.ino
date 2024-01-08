int ledPin = 13;
char setupLed = '0'; 
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}
void loop() 
{
  if (Serial.available() > 0) 
  {
    setupLed = Serial.read(); 
  }

  switch (setupLed) 
  {
    case '1': {
      digitalWrite(ledPin, HIGH);
      break;
    }
    case '0': {
      digitalWrite(ledPin, LOW);
      break;
    }
  }
}
