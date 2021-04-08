#ifndef POWER_H
#define POWER_H

#include <Arduino.h>
#include <entities/value.h>


class Power : public ValueABC<float> {
    public:
        Power():ValueABC(){};
        Power(float value, uint8_t source):ValueABC(value, source){};

};

#endif