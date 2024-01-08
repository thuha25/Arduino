//điều khiển tốc độ nháy led = biến trở 
int led = 9;
void setup(){
  pinMode(led,OUTPUT);
}
void loop(){
  int inputvalue = analogRead(A0);
  int x = map(inputvalue,0,1023,100,2000);
  digitalWrite(led,HIGH);
  delay(x);
  digitalWrite(led,LOW);
  delay(x);
}

//điều khiển sáng tối led bằng biến trở
// int led = 9;  //chân sung
// void setup(){
//   pinMode(led,OUTPUT);
// }
// void loop(){
//   int inputval = analogRead(A0);
//   int x = map(inputval,0,1023,0,255);
//   analogWrite(led,x);
// }

//chân âm chân A0 chân 5v