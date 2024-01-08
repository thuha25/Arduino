#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "ANH MINH - ESP";
const char* password = "ComTMM0112";

#define ESP32
#define CONFIG_SELF_AP 1
/* ---------- SENSORS ---------- */
#define CONFIG_LIGHT_SENSOR 1
#define CONFIG_GAS_SENSOR 1
#define CONFIG_ULTRASONIC_SENSOR 1
#define CONFIG_LINE_SENSOR 1
#define CONFIG_JOYSTICK 1
#define CONFIG_DHT_SENSOR 0
/* ---------- MOTORS AND LIGHT ---------- */
#define CONFIG_LED_CONTROL 1
#define CONFIG_DC_MOTOR 1
#define CONFIG_STEPPER_MOTOR 0
#define CONFIG_SERVO 0


/* ---------- SENSORS PINS ---------- */
#if CONFIG_LIGHT_SENSOR
#include "LightSensor.h"
#define LIGHT_SENSOR_PIN 35
#define LIGHT_SENSOR_URL "/light-sensor"
LightSensor light_sensor(LIGHT_SENSOR_PIN);
#endif

#if CONFIG_GAS_SENSOR
#include "GasSensor.h"
#define GAS_SENSOR_PIN 34
#define GAS_SENSOR_URL "/gas-sensor"
GasSensor gas_sensor(GAS_SENSOR_PIN);
#endif

#if CONFIG_ULTRASONIC_SENSOR
#include "UltrasonicSensor.h"
#define USENSOR_TRIG_PIN 14
#define USENSOR_ECHO_PIN 27
#define USENSOR_URL "/ultra-sonic-sensor"
UltrasnonicSensor u_sonic_sensor(USENSOR_TRIG_PIN, USENSOR_ECHO_PIN);
#endif

#if CONFIG_LINE_SENSOR
#include "LineSensor.h"
#define LINE_SENSOR_PIN 26
#define LINE_SENSER_URL "/line-sensor"
LineSensor line_sensor(LINE_SENSOR_PIN);
#endif

#if CONFIG_JOYSTICK
#include "JoyStick.h"
#define X_PIN 33
#define Y_PIN 32
#define BUTTON_PIN 25
#define JOYSTICK_URL "/joystick"
JoyStick joystick(X_PIN, Y_PIN, BUTTON_PIN);
#endif

#if CONFIG_DHT_SENSOR
#include<DHT.h>
#define DHT_PIN -1
#define DHT_TYPE DHT11
#define DHT_URL "/dht"
DHT dht(DHT_PIN, DHT_TYPE);
#endif

/* ---------- MOTORS AND LED PINS ---------- */

#if CONFIG_LED_CONTROL
#include "Led.h"
#define LED_PIN 21
#define LED_URL "/led"
Led led(LED_PIN);
#endif
#if CONFIG_DC_MOTOR
#include "DCMotor.h"
#define DC_IN1 2
#define DC_In2 4
#define DC_URL "/dc"
int clockwise = 1, speed = 250;
DCMotor dc(DC_IN1, DC_In2);
#endif
#if CONFIG_STEPPER_MOTOR
#include <Stepper.h>
#define STEP_PER_REV 2048
#define STEP_IN1 -1
#define STEP_IN2 -1
#define STEP_IN3 -1
#define STEP_IN4 -1
#define STEPPER_URL "/stepper"
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper stepper = Stepper(STEP_PER_REV, STEP_IN1, STEP_IN3, STEP_IN2, STEP_IN4);
int degreeToSteps(int degree, int STEPS = STEP_PER_REV) {
  if (degree == 0) return 0;
  return STEPS / (360 / degree);
}
#endif
#if CONFIG_SERVO
#include "MyServo.h"
#define SERVO_PIN -1
#define SERVO_URL "/servo"
#endif

WebServer server(80);

/* ---------- SENSORS HANDLERS ---------- */

#if CONFIG_LIGHT_SENSOR
void light_sensor_handler() {
  int val = light_sensor.read();
  server.send(200, "text/plain", String(val));
}
#endif

#if CONFIG_GAS_SENSOR
void gas_sensor_handler() {
  int val = gas_sensor.read();
  server.send(200, "text/plain", String(val));
}
#endif

#if CONFIG_ULTRASONIC_SENSOR
void ultrasonic_sensor_handler() {
  u_sonic_sensor.trigger();
  long duration = u_sonic_sensor.readDuration();
  float distance = u_sonic_sensor.readDistance();
  server.send(200, "application/json", "{\"duration\": " + String(duration) + ", \"distance\": " + String(distance) + "}");
}
#endif

#if CONFIG_LINE_SENSOR
void line_sensor_handler() {
  int val = line_sensor.read();
  server.send(200, "text/plain", String(val));
}
#endif

#if CONFIG_JOYSTICK
void joystick_handler() {
  int x = joystick.getX();
  int y = joystick.getY();
  bool isButtonDown = joystick.isButtonDown();
  server.send(200, "application/json", "{\"x\": " + String(x) + ", \"y\": " + String(y) + ", \"is_button_down\": " + (isButtonDown ? "true" : "false") + "}");
}
#endif

#if CONFIG_DHT_SENSOR
void dht_handler() {
  server.send(500, "text/plain", "Opps");
}
#endif

/* ---------- MOTORS HANDLERS ---------- */

#if CONFIG_LED_CONTROL
void led_handler() {
  if(server.hasArg("status")) {
    String status = server.arg("status");
    if(status != "on" && status != "off") {
      server.send(400, "text/plain", "Invalid argument. 'status' must be 'on' or 'off'.");
      return;
    }
    if(status == "on") {
      led.turnOn();
    } else if(status == "off") {
      led.turnOff();
    }
    server.send(200, "text/plain", "LED turned " + status);
  } else {
    server.send(400, "text/plain", "Missing argument: status");
  }
}
#endif
#if CONFIG_DC_MOTOR
void dc_handler() {
  if(server.hasArg("direction")) {
    int direction = server.arg("direction").toInt();
    if(direction != 0 && direction != 1) {
      server.send(400, "text/plain", "Invalid argument. 'direction' must be 0 or 1.");
      return;
    }
    clockwise = direction;
  }
  if(server.hasArg("speed")) {
    int speed = server.arg("speed").toInt();
    dc.setSpeed(speed);
  }
  if(clockwise)
    dc.rotateClockwise();
  else
    dc.rotateCounterClockwise();
  server.send(200, "text/plain", String("DC Motor is rotating ") + String(clockwise ? "clockwise" : "counter-clockwise") + String(" with the speed of ") + String(dc.speed));
}

#endif
#if CONFIG_STEPPER_MOTOR
void stepper_handler() {
  if(!server.hasArg("direction") && !server.hasArg("angle")) {
    server.send(400, "text/plain", "Invalid argument. Both 'direction' and 'angle' must be given.");
    return;
  }
  int direction = server.arg("direction").toInt();
  int angle = server.arg("angle").toInt();
  if (direction == 1) {
    angle = -angle;
  }

  stepper.step(degreeToSteps(angle));
  server.send(200, "text/plain", String("Stepper Motor rotated ") + String(clockwise ? "clockwise" : "counter-clockwise") + String(" with the angle of ") + String(angle));
}
#endif
#if CONFIG_SERVO
void servo_handler() {
  if(server.hasArg("status")) {
    String status = server.arg("status");
    if(status != "on" && status != "off") {
      server.send(400, "text/plain", "Invalid argument. 'status' must be 'on' or 'off'.");
      return;
    }
    if(status == "on") {
      startSwinging();
    } else if(status == "off") {
      stopSwinging();
    }
  }
  if(server.hasArg("angle")) {
    int angle = server.arg("angle").toInt();
    setAngle(angle);
  }
  if(isSwinging)
    server.send(200, "text/plain", String("Servo is swinging with the angle of ") + String(servoAngle));
  else
    server.send(200, "text/plain", "Servo is not swinging.");
}
#endif

void not_found_handler() {
  server.send(404, "text/plain", "Not active");
}

void setup() {
  Serial.begin(9600);
  #if CONFIG_SELF_AP
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();

    Serial.print("AP IP address: ");
    Serial.println(IP);
  #else
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("Local IP address: ");
    Serial.println(WiFi.localIP());
  #endif

  // Routes - Sensors
  #if CONFIG_LIGHT_SENSOR
  server.on(LIGHT_SENSOR_URL, HTTP_GET, light_sensor_handler);
  #endif

  #if CONFIG_GAS_SENSOR
  server.on(GAS_SENSOR_URL, HTTP_GET, gas_sensor_handler);
  #endif

  #if CONFIG_ULTRASONIC_SENSOR
  server.on(USENSOR_URL, HTTP_GET, ultrasonic_sensor_handler);
  #endif

  #if CONFIG_LINE_SENSOR
  server.on(LINE_SENSER_URL, HTTP_GET, line_sensor_handler);
  #endif

  #if CONFIG_JOYSTICK
  server.on(JOYSTICK_URL, HTTP_GET, joystick_handler);
  #endif

  #if CONFIG_DHT_SENSOR
  server.on(DHT_URL, HTTP_GET, dht_handler);
  #endif

  // Routes - Motors
  #if CONFIG_LED_CONTROL
  server.on(LED_URL, HTTP_GET, led_handler);
  #endif
  #if CONFIG_DC_MOTOR
  dc.rotateCounterClockwise();
  server.on(DC_URL, HTTP_GET, dc_handler);
  #endif
  #if CONFIG_STEPPER_MOTOR
  stepper.setSpeed(15);
  server.on(STEPPER_URL, HTTP_GET, stepper_handler);
  #endif
  #if CONFIG_SERVO
  servoAttach(SERVO_PIN);
  setupServo();
  stopSwinging();
  server.on(SERVO_URL, HTTP_GET, servo_handler);
  #endif


  server.onNotFound(not_found_handler);

  // servo.attach(SERVO_PIN);
  server.enableCORS();
  server.begin();

  // xTaskCreate(servoSpin, "servoSpin", 1024, NULL, 1, NULL);
}

void loop() {
  server.handleClient();
}