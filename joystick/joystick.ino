int Joystick_X = 0;
int Joystick_Y= 1;
int button = 5;
void setup() {
  pinMode(Joystick_X, INPUT); 
  pinMode(Joystick_Y, INPUT); 
  pinMode(button, INPUT_PULLUP); 
  Serial.begin(9600);
}
void loop() {
  int x, y, z;
  x = analogRead(Joystick_X);
  y = analogRead(Joystick_Y);
  z = digitalRead(button);
  Serial.print(x, DEC);
  Serial.print(", ");
  Serial.print(y, DEC);
  Serial.print(", ");
  Serial.println(z, DEC);
  delay(1000);
}