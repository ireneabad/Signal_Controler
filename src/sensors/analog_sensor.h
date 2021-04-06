#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H

#include <Arduino.h>
#include <sensors/sensors.h>


class AnalogSensor : public SensorABC<float> {
    public:
        AnalogSensor(uint8_t id, uint8_t pin):SensorABC<float>(id) {
            this->pin = pin;
        };
    private:
        uint8_t pin;
        float read();
};


float AnalogSensor::read() {
    return analogRead(this->pin);
    //return (map(analogRead(this->pin),0,1023,0,255));
}



#endif