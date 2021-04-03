#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <actuator/actuator.h>
#include <entities/signal.h>

class Motor : public ActuatorABC<float> {
    public:
        Motor(uint8_t id, uint8_t pin):ActuatorABC<float>(id){
            this->pin=pin;
        }
    private:
        uint8_t pin;
        void write(Signal value);
};

void Motor::write(Signal value) {
    analogWrite(this->pin, value.getValue());
}

#endif