#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <config.h>
#include <serializers/output.h>
#include <processors/circular_buffer.h>
#include <processors/trasnformer.h>

#include <sensors/analog_sensor.h>
#include <sensors/digital_sensor.h>
#include <sensors/temperature/lm35.h>
#include <actuator/motor.h>
//#include <actuator/led.h>




namespace CONFIG {
    const uint8_t SENSOR_INPUNT = A3; 
}

void setup() {
  Serial.begin(9600);
  
  pinMode(analog_sensor.pin(), INPUT);
  pinMode(13, OUTPUT);
  pinMode(motor.pin1(), OUTPUT);
  pinMode(motor.pin2(), OUTPUT);
  pinMode(motor.pin3(), OUTPUT);
  pinMode(motor.pin4(), OUTPUT);
 
}

#endif