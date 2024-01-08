int JoyStick_X = A0;
int JoyStick_Y = A1;
int button = 5;
int ledLeft = 2;
int ledRight = 3;
int ledUp = 4;
int ledDown = 6;
bool isButtonPressed = false;
bool isLeftOn = false;
bool isRightOn = false;
bool isUpOn = false;
bool isDownOn = false;

void setup()
{
  pinMode(JoyStick_X, INPUT);
  pinMode(JoyStick_Y, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(ledLeft, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledUp, OUTPUT);
  pinMode(ledDown, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int x, y, z;
  x = analogRead(JoyStick_X);
  y = analogRead(JoyStick_Y);
  z = digitalRead(button);

  if (x > 500)
  {
    digitalWrite(ledRight, HIGH);
    isRightOn = true;
  }
  else if (x < 100)
  {
    digitalWrite(ledLeft, HIGH);
    isLeftOn = true;
  }
  else if (!isButtonPressed)
  {
    digitalWrite(ledLeft, isLeftOn);
    digitalWrite(ledRight, isRightOn);
  }

  if (y > 500)
  {
    digitalWrite(ledDown, HIGH);
    isDownOn = true;
  }
  else if (y < 100)
  {
    digitalWrite(ledUp, HIGH);
    isUpOn = true;
  }
  else if (!isButtonPressed)
  {
    digitalWrite(ledUp, isUpOn);
    digitalWrite(ledDown, isDownOn);
  }

  if (z == LOW && !isButtonPressed)
  {
    isButtonPressed = true;
    isLeftOn = false;
    isRightOn = false;
    isUpOn = false;
    isDownOn = false;
  }
  else if (z == HIGH)
  {
    isButtonPressed = false;
  }

  Serial.print(x, DEC);
  Serial.print(", ");
  Serial.print(y, DEC);
  Serial.print(", ");
  Serial.println(z, DEC);
}