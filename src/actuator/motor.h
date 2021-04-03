#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <actuator/actuator.h>
#include <entities/signal.h>

class Motor : public ActuatorABC<float> {
    public:
        Motor(uint8_t id, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4):ActuatorABC<float>(id){
            this->pin1=pin1;
            this->pin2=pin2;
            this->pin3=pin3;
            this->pin4=pin4;
            
        }
    private:
        uint8_t pin1;
        uint8_t pin2;
        uint8_t pin3;
        uint8_t pin4;
        void write(Signal value);
};

void Motor::write(Signal value) {
    int paso [8][4] =
    {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
    };

     for (int i = 0; i < 8; i++)
    {
      digitalWrite(pin1, paso[i][0]);
      digitalWrite(pin2, paso[i][1]);
      digitalWrite(pin3, paso[i][2]);
      digitalWrite(pin4, paso[i][3]);
      delay(value.getValue());
    }

}

#endif