#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <actuator/actuator.h>
#include <entities/signal.h>
#include <entities/value.h>

//Actuador tipo LED

class Led : public ActuatorABC<bool> {
    public:
        Led(uint8_t id, uint8_t pin):ActuatorABC(id){
            this->pin=pin;
        }
    private:
        uint8_t pin;
        void write(Signal value);
};


void Led::write(Signal value) {
    digitalWrite(this->pin, value.getValue());
}

#endif