const int cambien = A0; 
const int giatriLedPin = 8; 
const int buzzerPin = 9; 
float sinVal;
int toneVal;
long duration;
float distance;
int giatri;
void setup() {
  Serial.begin(9600);
  pinMode(giatriLedPin, OUTPUT);
  pinMode(cambien, INPUT);
}
void loop() {
  giatri = analogRead(cambien); // Đọc giá trị analog từ cảm biến và gán vào biến giatri
  if (giatri > 200) { // Nếu giá trị cảm biến gas lớn hơn 600
    // Đèn LED sáng
    digitalWrite(giatriLedPin, HIGH); 
    // Buzzer phát ra tiếng cảnh báo
    for(int x=0; x<180; x++){
    sinVal = sin(x*(3.2423/180));
    toneVal = 2000 + (int(sinVal *1000));
    tone(buzzerPin, toneVal);
    }
  } else {
    digitalWrite(giatriLedPin, LOW); // Đèn LED tắt
    noTone(buzzerPin); // Tắt buzzer
  }
  Serial.print("Giá trị cảm biến: ");
  Serial.println(giatri);
  delay(200);
}