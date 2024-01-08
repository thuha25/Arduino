#include <Scheduler.h>
#include <Task.h>
#include <LeanTask.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <Servo.h>
#include <Stepper.h> 


// Thiết lập thông số cho WiFi
const char* ssid = "Ha ngu";
const char* password = "25032003";

// Khởi tạo đối tượng máy chủ web
ESP8266WebServer server(80);

// Thiết lập cổng cho DHT và Servo
// int LED = 5; // GPIO5 (D1)

#define DHTPIN 2
#define DHTTYPE DHT11
#define SERVO_PIN 14
// #define   LED 5
// #define LIGHT A0
#define LINE 0  //D1
#define trigPin 9
#define echoPin 10
#define in1 15
#define in2 4

const int STEPS = 2048; // Số bước trong một vòng
Stepper myStepper = Stepper(STEPS, 15, 12, 13, 14);
int degreeToSteps(int degree, int STEPS = 2048)
{
    if (degree == 0)
        return 0;
    return STEPS / (360 / degree);
}

DHT dht(DHTPIN, DHTTYPE);
Servo servo;

// void handleLEDOn() {
//   Serial.println("led on");
//   // Xử lý bật đèn LED ở đây
//   digitalWrite(LED, HIGH); 
//   server.send(200, "text/plain", "Đèn đã được bật");
// }

// void handleLEDOff() {
//   Serial.println("led off");
//   digitalWrite(LED, LOW); // Turn LED OFF
//   server.send(200, "text/plain", "Đèn đã được tắt");
// }
int servo_angle = 90;
class BlinkTask : public Task {
 protected:
  void setup() {
  }

  void loop() {
    servo.write(servo_angle*2);
    delay(1000);
    servo.write(0);
    delay(1000);
  }

} servoSpin;

void handleTemp() {
  // Đọc nhiệt độ từ cảm biến DHT
  float temperature = dht.readTemperature();
  Serial.println(temperature);
  if (isnan(temperature)) {
    server.send(500, "text/plain", "Lỗi khi đọc nhiệt độ từ cảm biến");
  } else {
    server.send(200, "text/plain", String(temperature));
  }
}

void handleHum() {
  // Đọc độ ẩm từ cảm biến DHT
  float humidity = dht.readHumidity();
  Serial.println(humidity);
  if (isnan(humidity)) {
    server.send(500, "text/plain", "Lỗi khi đọc độ ẩm từ cảm biến");
  } else {
    server.send(200, "text/plain", String(humidity));
  }
}

void handleServo() {
  // Xử lý vận hành Servo ở đây, dựa trên tham số được truyền (eg)
  if (server.hasArg("angle")) {
    servo_angle = server.arg("angle").toInt();
    // Serial.println(servo_angle);
    // servo.write(servo_angle*2);
    // delay(1000);
    // servo.write(0);
    // delay(1000);
    server.send(200, "text/plain", "Servo đã được điều khiển");
  } else {
    server.send(400, "text/plain", "Thiếu tham số cho Servo");
  }
}

// void handleLight() {
//   int value;
//   value = analogRead(LIGHT);
//   server.send(200, "text/plain", String(value));
// }
void handleLine() {
  int value;
  value = digitalRead(LINE);
  Serial.println(value);
  server.send(200, "text/plain", String(value));
}
void handleUtra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  server.send(200, "text/plain",String(distance));
}
void handleStepper(){
  // int direction = server.hasArg("direction")
  if(server.hasArg("direction")) {
    int direction = server.arg("direction").toInt();
    if(direction){
        myStepper.setSpeed(14);          // 18 RPM - Rotations per minute
        int degreeC = degreeToSteps(45); 
        myStepper.step(degreeC);         // quay thuan chiều kim đồng hồ
    }else{
        myStepper.setSpeed(14); // 14 RPM - Rotations per minute
        int degreeCC = degreeToSteps(90);
        myStepper.step(-degreeCC); // quay nguoc chiều kim đồng hồ - quay 1 vòng
    }
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "No direction arg");
  }
}
void handleDC(){
  if (server.hasArg("direction") && server.hasArg("speed") ) {
    int direction = server.arg("direction").toInt();
    int speed = server.arg("speed").toInt();
    if (direction) {
      analogWrite(in1, speed);
      digitalWrite(in2, LOW);
    }else{
      digitalWrite(in1, LOW);
      analogWrite(in2, speed);
    }
    server.send(200, "text/plain", "OK");
  }else {
    server.send(400, "text/plain", "No direction arg");
  }
}
void setup() {
  // Khởi động Serial để theo dõi thông tin debug
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myStepper.setSpeed(14);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(LINE,OUTPUT);
  // Kết nối WiFi
  // WiFi.begin(ssid, password);
  WiFi.softAP(ssid, password);
  // Serial.println("Kết nối đến WiFi");
  // while (WiFi.status() != WL_CONNECTED) {
  //   Serial.print(".");
  //   delay(1000);
  // }
  // Serial.println("Đã kết nối thành công!");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
  // Định nghĩa các endpoint và gán hàm xử lý tương ứng
  // server.on("/led=on", handleLEDOn);
  // server.on("/led=off", handleLEDOff);
  // server.on("/dht/temp", handleTemp);
  // server.on("/dht/hum", handleHum);
  server.on("/servo", HTTP_GET, handleServo);
  // server.on("/light", HTTP_GET, handleLight);
  server.on("/line", HTTP_GET, handleLine);
  server.on("/utra",HTTP_GET,handleUtra);
  server.on("/stepper",HTTP_GET,handleStepper);
  server.on("/dc",HTTP_GET,handleDC);
  // Khởi động máy chủ
  server.enableCORS(true);
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address of network: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  // Bắt đầu cảm biến DHT và Servo
  dht.begin();
  servo.attach(SERVO_PIN);
  // pinMode(LED,OUTPUT);
  Scheduler.start(&servoSpin);

  Scheduler.begin();
}

void loop() {
  server.handleClient(); // Xử lý các yêu cầu từ client
}
