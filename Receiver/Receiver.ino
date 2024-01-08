#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2
#define LED 13

bool LED_VAL = false;
void setup()
{
  pinMode(LED, OUTPUT);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void loop()
{
  if (IrReceiver.decode())
  {
    uint32_t val = IrReceiver.decodedIRData.decodedRawData;
    if (val == 1)
    {
      LED_VAL = !LED_VAL;
      digitalWrite(LED, LED_VAL);
    }
    IrReceiver.resume();
  }
}
