#include <Scheduler.h>
#include <Task.h>
#include <LeanTask.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include <DHT.h>
#include <Servo.h>


// Thiết lập thông số cho WiFi
const char* ssid = "...";
const char* password = "00000000";

// Khởi tạo đối tượng máy chủ web
ESP8266WebServer server(80);

// Thiết lập cổng cho DHT và Servo
int LED = 5; // GPIO5 (D1)

#define DHTPIN 2
#define DHTTYPE DHT11
#define SERVO_PIN 4
#define LED 5
#define LIGHT A0

// DHT dht(DHTPIN, DHTTYPE);
Servo servo;

void handleLEDOn() {
  Serial.println("led on");
  // Xử lý bật đèn LED ở đây
  digitalWrite(LED, HIGH); 
  server.send(200, "text/plain", "Đèn đã được bật");
}

void handleLEDOff() {
  Serial.println("led on");
  digitalWrite(LED, LOW); // Turn LED OFF
  server.send(200, "text/plain", "Đèn đã được tắt");
}
int servo_angle = 0;
class BlinkTask : public Task {
 protected:
  void setup() {
  }

  void loop() {
    servo.write(servo_angle);
    delay(1000);
    servo.write(0);
    delay(1000);
  }

} servoSpin;
void handle_light(){
  int light_val = analogRead(LIGHT);
  server.send(200, "application/json", "{\"light\":" + String(light_val) + "}");
}

// void handleTemp() {
//   // Đọc nhiệt độ từ cảm biến DHT
//   float temperature = dht.readTemperature();
//   Serial.println(temperature);
//   if (isnan(temperature)) {
//     server.send(500, "text/plain", "Lỗi khi đọc nhiệt độ từ cảm biến");
//   } else {
//     server.send(200, "text/plain", String(temperature));
//   }
// }

// void handleHum() {
//   // Đọc độ ẩm từ cảm biến DHT
//   float humidity = dht.readHumidity();
//   Serial.println(humidity);
//   if (isnan(humidity)) {
//     server.send(500, "text/plain", "Lỗi khi đọc độ ẩm từ cảm biến");
//   } else {
//     server.send(200, "text/plain", String(humidity));
//   }
// }

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


void setup() {
  // Khởi động Serial để theo dõi thông tin debug
  Serial.begin(9600);

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.println("Kết nối đến WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Đã kết nối thành công!");
  // Định nghĩa các endpoint và gán hàm xử lý tương ứng
  server.on("/led=on", handleLEDOn);
  server.on("/led=off", handleLEDOff);
  // server.on("/dht/temp", handleTemp);
  // server.on("/dht/hum", handleHum);
  server.on("/servo", HTTP_GET, handleServo);
  server.on("/light", handle_light);

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
  // dht.begin();
  servo.attach(SERVO_PIN);
  pinMode(LED,OUTPUT);
  Scheduler.start(&servoSpin);

  Scheduler.begin();
}

void loop() {
  // Serial.println("Light: "+ light_val);
  // if (light_val > 1000) servo_angle = 90;
  // else servo_angle = 180;
  server.handleClient(); // Xử lý các yêu cầu từ client
}
