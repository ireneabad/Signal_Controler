#ifndef PWM_H
#define PWM_H

#include <Arduino.h>
#include <entities/value.h>


class Signal : public ValueABC<uint8_t> {
    public:
        Signal():ValueABC(){};
        Signal(uint8_t value, uint8_t source):ValueABC(value, source){};
};

#endif