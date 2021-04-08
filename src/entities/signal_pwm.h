#ifndef SIGNAL_PWM_H
#define SIGNAL_PWM_H

#include <Arduino.h>
#include <entities/value.h>


class SignalPWM : public ValueABC<uint8_t> {
    public:
        SignalPWM():ValueABC(){};
        SignalPWM(uint8_t value, uint8_t source):ValueABC(value, source){};
        uint8_t getValue();
    private:
        uint8_t value;
};

uint8_t SignalPWM::getValue() {
    return this->value;
}

#endif