int led[] = {2,3,4,5,6,7,8,9,10,11};
int i;
void setup(){
  for(i=0;i<=9;i++){
    pinMode(led[i],OUTPUT);
  }
}
//cau1:10 led nhấp nháy

// void BlinkLed(){
//   for(i=0;i<=9;i++)
//     digitalWrite(led[i],HIGH);
//     delay(600);
//   for(i=0;i<=9;i++)
//     digitalWrite(led[i],LOW);
//     delay(600);
// }
// void loop(){
//   BlinkLed();
// }

//cau2:10 led chạy từ trái sang phải, phải sang trái
// void chaytraiphai(){
//   static int chay1=0;
//   for(i=0;i<=9;i++){
//     digitalWrite(led[i],LOW);
//   }
//   digitalWrite(led[chay1],HIGH);
//   delay(600);
//   chay1++;
//   if(chay1>=10)
//     chay1=0;
// }
// void chayphaitrai(){
//   static int chay1=9;
//   for(i=0;i<=9;i++){
//     digitalWrite(led[i],LOW);
//   }
//   digitalWrite(led[chay1],HIGH);
//   delay(600);
//   chay1--;
//   if(chay1<0)
//     chay1=9;
// }
// void loop(){
//   chaytraiphai();
//   // chayphaitrai();
// }

//cau 4:10 led sáng dồn và tắt dồn tư trái qua phải, phải qua trái
// void dontraiphai(){
//   static int chay1=0;
//   for(i=0;i<=9;i++){
//     digitalWrite(led[i],LOW);
//     delay(600);
//   }
//   for(chay1=0;chay1<=9;chay1++){
//     digitalWrite(led[chay1],HIGH);
//     delay(600);
//   }
// }
// void donphaitrai(){
//   static int chay1=9;
//   for(chay1=9;chay1>=0;chay1--){
//     digitalWrite(led[chay1],HIGH);
//     delay(600);
//   }
//   for(chay1=9;chay1>=0;chay1--){
//     digitalWrite(led[chay1],LOW);
//     delay(600);
//   }
// }
// void loop(){
//   // dontraiphai();
//   donphaitrai();
// }

//cau6:10 led sáng dồn và tắt dồn từ 2 bên vào trong, từ trong ra ngoài
// void ngoaitrong(){
//   for(i=0;i<10;i++)
//     digitalWrite(led[i],LOW);
//   delay(600);
//   digitalWrite(led[0],HIGH);
//   digitalWrite(led[9],HIGH);
//   delay(600);
//   digitalWrite(led[1],HIGH);
//   digitalWrite(led[8],HIGH);
//   delay(600);
//   digitalWrite(led[2],HIGH);
//   digitalWrite(led[7],HIGH);
//   delay(600);
//   digitalWrite(led[3],HIGH);
//   digitalWrite(led[6],HIGH);
//   delay(600);
//   digitalWrite(led[4],HIGH);
//   digitalWrite(led[5],HIGH);
//   delay(600);
//   digitalWrite(led[0],LOW);
//   digitalWrite(led[9],LOW);
//   delay(600);
//   digitalWrite(led[1],LOW);
//   digitalWrite(led[8],LOW);
//   delay(600);
//   digitalWrite(led[2],LOW);
//   digitalWrite(led[7],LOW);
//   delay(600);
//   digitalWrite(led[3],LOW);
//   digitalWrite(led[6],LOW);
//   delay(600);
//   digitalWrite(led[4],LOW);
//   digitalWrite(led[5],LOW);
//   delay(600);
// }
// void trongngoai(){
//   for(i=0;i<10;i++)
//     digitalWrite(led[i],LOW);
//   delay(600);
//   digitalWrite(led[4],HIGH);
//   digitalWrite(led[5],HIGH);
//   delay(600);
//   digitalWrite(led[3],HIGH);
//   digitalWrite(led[6],HIGH);
//   delay(600);
//   digitalWrite(led[2],HIGH);
//   digitalWrite(led[7],HIGH);
//   delay(600);
//   digitalWrite(led[1],HIGH);
//   digitalWrite(led[8],HIGH);
//   delay(600);
//   digitalWrite(led[0],HIGH);
//   digitalWrite(led[9],HIGH);
//   delay(600);
//   digitalWrite(led[4],LOW);
//   digitalWrite(led[5],LOW);
//   delay(600);
//   digitalWrite(led[3],LOW);
//   digitalWrite(led[6],LOW);
//   delay(600);
//   digitalWrite(led[2],LOW);
//   digitalWrite(led[7],LOW);
//   delay(600);
//   digitalWrite(led[1],LOW);
//   digitalWrite(led[8],LOW);
//   delay(600);
//   digitalWrite(led[0],LOW);
//   digitalWrite(led[9],LOW);
//   delay(600);
// }
// void loop(){
//   // ngoaitrong();
//   trongngoai();
// }
// cau8:8 led sáng xen kẽ
// void xenke(){
//   for(i=0;i<=9;i+=2)
//     digitalWrite(led[i],HIGH);
//     delay(600);
//   for(i=0;i<=9;i++)
//     digitalWrite(led[i],LOW);
//   for(i=1;i<=9;i+=2)
//     digitalWrite(led[i],HIGH);
//     delay(600);
//   for(i=0;i<=9;i++)
//     digitalWrite(led[i],LOW);
// }
// void loop(){
//   xenke();
// }
