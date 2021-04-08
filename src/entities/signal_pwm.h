#ifndef SIGNAL_PWM_H
#define SIGNAL_PWM_H

#include <Arduino.h>
#include <entities/value.h>


class SignalPWM : public ValueABC<int> {
    public:
        SignalPWM():ValueABC(){};
        SignalPWM(int value, uint8_t source):ValueABC(value, source){};
};

#endif