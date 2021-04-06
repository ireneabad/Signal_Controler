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
#include <entities/power.h>
#include <entities/value.h>


CircularBuffer<int> circular = CircularBuffer<int>(30);
AnalogSensor pot_sensor = AnalogSensor(0x7A, A3);
Motor motor = Motor(0xAB, 8, 9, 10, 11);
Led led = Led(0xAC, 13);



void loop() {
  pot_sensor.excecute();
  if(pot_sensor.hasChanged()){
    ValueABC<float> value = pot_sensor.getValue();

    circular.append(value.getValue()); // Prefuntar si tiene que tener doble getValue
    int mean = circular.mean();

    float scaled_read = scaler<int>(value.getValue(), 2.0);
    float mapped_read = analog_map<int>(value.getValue(), 0,100);

    valuePrinter(Serial, value.getValue(), "Lectura potenciometro");
    valuePrinter(Serial, mean, "Mean Value");
    valuePrinter(Serial, scaled_read, "Lectura escalada");
    valuePrinter(Serial, mapped_read, "Lectura mapeada");
    
    Signal bool_value = Signal((50 < mapped_read),0);
    //digitalWrite(13,bool_value);

    motor.setValue(mapped_read);
    led.setValue();
   
  }
  motor.excecute();
  led.excecute();
  //digitalWrite(13,HIGH);


}