#include <Arduino.h>
#include <Model.h>
#include "constants.h"
using namespace std;

ModelInit Model1(3, 12, 9, WB::W, WB::B);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

  Serial.println(Model1.predict(199, 116, 119));
  Serial.println(millis());
}