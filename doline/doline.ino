#define LINE 4
#define led 13
#define BellPin 11
int value = 0;
int x = 0;
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  pinMode(LINE, INPUT);
  pinMode(BellPin, OUTPUT);
}

void loop() {
  value = digitalRead(LINE);
  Serial.println(value);
  x = (x + 1) % 180;
  int val = 1000 * sin(x * 3.14 / 180);
  if(value == 0) {
    digitalWrite(led, HIGH);
    tone(BellPin, val);
  } else {
    digitalWrite(led, LOW);
    noTone(BellPin);
  }
  delay(10);
}
