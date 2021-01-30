
#include <Moonmachine.h>
#include "constants.h"

using namespace std;

ModelInit Model1(3, 12, 9, WB::W, WB::B);
Adafruit_TCS34725 SENSOR = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
Moonmachine Machine(Model1, SENSOR);
void isr()
{
  Machine.detect();
}
void setup()
{
  Serial.begin(9600);
  Machine.sensor_init();
  pinMode(pins::interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pins::interruptPin), isr, FALLING);
}

void loop()
{
  Machine.run();
}
