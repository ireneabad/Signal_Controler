#ifndef SIGNAL_H
#define SIGNAL_H

#include <Arduino.h>
#include <entities/value.h>


class Signal : public ValueABC<bool> {
    public:
        Signal():ValueABC(){};
        Signal(bool value, uint8_t source):ValueABC(value, source){};
        bool getValue();
    private:
        bool value;
};

bool Signal::getValue() {
    return this->value;
}
#endif