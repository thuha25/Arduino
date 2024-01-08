#include<Servo.h>
extern Servo servo;
extern int servoAngle;
extern bool isSwinging;

void servoAttach(int pin);
void setAngle(int angle);
void startSwinging();
void stopSwinging();
void swing();
void setupServo();