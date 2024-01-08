#include<WiFi.h>
#include<WebServer.h>
#include "SPIFFS.h"
#include<DHT.h>
#include <ESP32Servo.h>

const char* ssid = "MLDH - ESP32";
const char* password = "123456789";

// IPAddress local_ip(192,168,1,1);
// IPAddress gateway(192,168,1,1);
// IPAddress subnet(255,255,255,0);
WebServer server(80);

#define LED 15

// #define DHT_PIN 2
// #define DHT_TYPE DHT11

#define LINE_PIN 2

#define SERVO_PIN 4
#define ENA 18
#define IN1 19
#define IN2 21

// DHT dht(DHT_PIN, DHT_TYPE);
// Servo servo;

void setup_led() {
  pinMode(LED, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(LINE_PIN, INPUT);
}

int servo_angle = 0;

void setup() {
  Serial.begin(115200);
  setup_led();

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  // WiFi.softAPConfig(local_ip, gateway, subnet);

  Serial.print("AP IP address: ");
  Serial.println(IP);

  Serial.print("Local IP address: ");
  Serial.println(WiFi.localIP());

  // Routes
  server.on("/", handle_index);
  server.on("/led", handle_led);
  // server.on("/dht", handle_dht);
  // server.on("/servo", handle_servo);
  server.on("/line", handle_line);
  server.on("/dc", handle_dc);
  pinMode(LED, OUTPUT);

  // servo.attach(SERVO_PIN);
  server.enableCORS();
  server.begin();

  // xTaskCreate(servoSpin, "servoSpin", 1024, NULL, 1, NULL);
}

// void servoSpin(void* args) {
//   while(1) {
//     servo.write(servo_angle);
//     delay(1000);
//     servo.write(0);
//     delay(1000);
//   }
// }

String get_html(const char* path) {
  File file = SPIFFS.open(path, "r");
  if(!file) {
    Serial.println("Could not open file for reading");
    Serial.print("File: ");
    Serial.println(path);
    return "Sorry but no luck!";
  }
  String content = file.readString();
  return content;
}

void handle_index() {
  Serial.println("Request /");
  server.send(200, "text/html", get_html("/index.html"));
}

void handle_led() {
  if(server.hasArg("status")) {
    String status = server.arg("status");
    if(status == "on") {
      digitalWrite(LED, HIGH);
    } else if(status == "off") {
      digitalWrite(LED, LOW);
    }
    server.send(200, "application/json", "{\"message\": \"OK\"}");
  } else {
    server.send(400, "application/json", "{\"error\": \"Missing argument: status\"}");
  }
}

void handle_line() {
  int val = digitalRead(LINE_PIN);
  server.send(200, "application/json", "{\"line\":" + String(std::to_string(val).c_str()) + "}");
}
// void handle_dht() {
//   float temperature = dht.readTemperature();
//   float humidity = dht.readHumidity();
//   Serial.print("Temp: ");
//   Serial.println(temperature);
//   Serial.print("Humid: ");
//   Serial.println(humidity);

//   if(isnan(temperature) || isnan(humidity)) {
//     server.send(500, "application/json", "{\"error\": \"Error occured when reading DHT\"}");
//   } else {
//     String response = "{\"temperature\": " + String(std::to_string(temperature).c_str()) + ", \"humidity\":" + String(std::to_string(humidity).c_str()) + "}";
//     server.send(200, "application/json", response);
//   }
//   // TO-DO
// }

void handle_dc() {
  if(server.hasArg("direction")) {
    int direction = server.arg("direction").toInt();
    if(direction == 1) {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 150);
    }  else {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 150);
    }
    server.send(200, "application/json", "{\"message\": \"OK\"}");
  } else {
    server.send(400, "application/json", "{\"error\": \"Missing argument: direction\"}");
  }
}

// void handle_servo() {
//   if(server.hasArg("angle")) {
//     int angle = server.arg("angle").toInt();
//     servo_angle = angle;
//     servo.write(angle);
//     Serial.println(angle);
//     server.send(200, "application/json", "{\"message\": \"OK\"}");
//   } else {
//     server.send(400, "application/json", "{\"error\": \"Missing argument: angle\"}");
//   }
// }

void loop() {
  server.handleClient();
}