#include <Arduino.h>
#include <Model.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
class Moonmachine
{
private:
    void getRawData_noDelay(uint16_t &redSensor, uint16_t &greenSensor, uint16_t &blueSensor, uint16_t &clearSensor);
    uint16_t redSensor;
    uint16_t greenSensor;
    uint16_t blueSensor;
    uint16_t clearSensor;
    volatile bool objDetection;
    void readSensor();
    ModelInit predictionModel;
    Adafruit_TCS34725 sesnor;

public:
    Moonmachine(ModelInit &model, Adafruit_TCS34725 &sensor);
    void run();
    void detect();
    void sensor_init();
};