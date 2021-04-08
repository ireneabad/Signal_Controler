#include <Arduino.h>
#include <config.h>
#include <serializers/output.h>
#include <processors/circular_buffer.h>
#include <processors/trasnformer.h>
#include <sensors/analog_sensor.h>
#include <sensors/digital_sensor.h>
#include <sensors/temperature/lm35.h>
#include <actuator/motor.h>
#include <actuator/led.h>
#include <entities/signal.h>
#include <entities/signal_pwm.h>
#include <entities/power.h>
#include <entities/value.h>


CircularBuffer<int> circular = CircularBuffer<int>(30);
AnalogSensor pot_sensor = AnalogSensor(0x7A, A3);
Motor motor = Motor(0xAB, 8, 9, 10, 11);
Led led = Led(0xAC, 13);



void loop() {
  pot_sensor.excecute();
  if(pot_sensor.hasChanged()){
    Power sensor_value = Power(pot_sensor.getValue().getValue(),0);

    circular.append(sensor_value.getValue()); // Prefuntar si tiene que tener doble getValue
    int mean = circular.mean();

    float scaled_read = scaler<int>(sensor_value.getValue(), 2.0);
    SignalPWM mapped_read = SignalPWM(analog_map<int>(sensor_value.getValue(), 0,100),0);

    valuePrinter(Serial, sensor_value.getValue(), "Lectura potenciometro");
    valuePrinter(Serial, mean, "Mean Value");
    valuePrinter(Serial, scaled_read, "Lectura escalada");
    valuePrinter(Serial, mapped_read.getValue(), "Lectura mapeada");
    
    Signal bool_value = Signal((50 < mapped_read.getValue()),0);
    digitalWrite(13,bool_value.getValue());

    //motor.setValue(mapped_read.getValue());
    //led.setValue(bool_value.getValue());
   
    //motor.excecute();
    //led.excecute();
  }

 
  //digitalWrite(13,HIGH);


}