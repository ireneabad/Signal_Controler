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

// Programa para controlar un LED y un motor paso a paso utilizando un potenciometro
//Inicialización de los actuadores y sensores
CircularBuffer<float> circular = CircularBuffer<float>(30);
AnalogSensor pot_sensor = AnalogSensor(0x7A, A3);
Motor motor = Motor(0xAB, 8, 9, 10, 11);
Led led = Led(0xAC, 13);

void loop() {

  //Ejecutar el sensor para que saber si el valor está cambiando
  pot_sensor.excecute();  
  if(pot_sensor.hasChanged()){
    // TODO: Make sensor output the right kind of value (Irene)
    Power sensor_value = Power(pot_sensor.getValue().getValue(), 0);  // Se utiliza la variable Power para gardar el valor de la lectura del potenciometro

    circular.append(sensor_value.getValue()); // Circular append de 30 valores para calcular el promedio
    int mean = int(circular.mean());

    float scaled_read = scaler<int>(sensor_value.getValue(), 2.0);  //Escala el valor por dos
    SignalPWM mapped_read = SignalPWM(analog_map<int>(sensor_value.getValue(), 0, 100), 0);  //Mapea el valor del potenciometro de 0 a 100 y lo guarda en una variable tipo SigmalPWM


    //Muestra la lectura con diferentes transformaciones
    valuePrinter(Serial, sensor_value.getValue(), "Lectura potenciometro");
    valuePrinter(Serial, mean, "Mean Value");
    valuePrinter(Serial, scaled_read, "Lectura escalada");
    valuePrinter(Serial, mapped_read.getValue(), "Lectura mapeada");
    
    Signal bool_value = Signal((50 > mapped_read.getValue()),0); //Transforma la señal mapeada en un valor booleano

  //Setea los valores en los actuadores 
    motor.setValue(mapped_read.getValue()); 
    led.setValue(bool_value);

    motor.excecute();
    led.excecute();

    //digitalWrite(13,bool_value.getValue());
  }
}