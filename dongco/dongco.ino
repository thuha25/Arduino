int in1 = 9;
int in2 = 8;
int speed = 150;

int ledPin = 13;

void setup()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  analogWrite(in1, 100);
  digitalWrite(in2, LOW);
}