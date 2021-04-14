#ifndef SIGNAL_H
#define SIGNAL_H

#include <Arduino.h>
#include <entities/value.h>

//Variavle Signal que solo admite valores tipo booleanos

class Signal : public ValueABC<bool> {
    public:
        Signal():ValueABC(){};
        Signal(bool value, uint8_t source):ValueABC(value, source){};

};

#endif