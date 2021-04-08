#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <entities/value.h>
#include <entities/signal.h>
#include <entities/signal_pwm.h>
#include <entities/power.h>

template<class T>
class ActuatorABC {
    public:
        ActuatorABC(uint8_t id);
        void setValue(T value);
        ValueABC<T> getValue();
        uint8_t getId();
        void excecute();
    private:
        bool hasToChange;
        T value;
        uint8_t id;
        virtual void write(T value);
};

template<class T>
ActuatorABC<T>::ActuatorABC(uint8_t id){
    this->id = id;
}

template<class T>
void ActuatorABC<T>::setValue(T value) {
    this->hasToChange = true;
    this->value = value;
}

template<class T>
uint8_t ActuatorABC<T>::getId() {
    return this->id;
}

template<class T>
void ActuatorABC<T>::excecute() {
    if (this->hasToChange) {
        this->write(this->value);
        this->hasToChange = false;
    }
}

//Para obtener estado del actuador, no se está utilizando
template<class T>
ValueABC<T> ActuatorABC<T>::getValue() {
    return this->value;
}

#endif