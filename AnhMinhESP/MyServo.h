#ifdef ARDUINO_UNO
#include<Servo.h>
#else
#include<ESP32Servo.h>
#endif
extern Servo servo;
extern int servoAngle;
extern bool isSwinging;

void servoAttach(int pin);
void setAngle(int angle);
void startSwinging();
void stopSwinging();
void swing();
void setupServo();