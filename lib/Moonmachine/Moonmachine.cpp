#include <Moonmachine.h>

Moonmachine::Moonmachine(ModelInit &model, Adafruit_TCS34725 &sensor)
{
    this->objDetection = false;
    this->sesnor = sensor;
    this->predictionModel = model;
}
void Moonmachine::detect()
{
    this->objDetection = true;
}
void Moonmachine::sensor_init()
{
    // On génère une interruption à chaque cycle
    this->sesnor.write8(TCS34725_PERS, TCS34725_PERS_NONE);
    // Activer la fonction d'interruption du capteur
    this->sesnor.setInterrupt(true);
}
void Moonmachine::getRawData_noDelay(uint16_t &redSensor, uint16_t &greenSensor, uint16_t &blueSensor, uint16_t &clearSensor)
{
    this->clearSensor = this->sesnor.read16(TCS34725_CDATAL);
    this->redSensor = this->sesnor.read16(TCS34725_RDATAL);
    this->greenSensor = this->sesnor.read16(TCS34725_GDATAL);
    this->blueSensor = this->sesnor.read16(TCS34725_BDATAL);
}
void Moonmachine::readSensor()
{
    this->getRawData_noDelay(this->redSensor, this->greenSensor, this->blueSensor, this->clearSensor);
    this->sesnor.clearInterrupt();
    this->objDetection = false;
}
void Moonmachine::run()
{
    if (this->objDetection)
    {
        this->readSensor();
        this->predictionModel.predict(this->redSensor, this->greenSensor, this->blueSensor);
    }
}
