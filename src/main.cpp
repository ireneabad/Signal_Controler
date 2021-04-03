#include <Arduino.h>
#include <config.h>
#include <serializers/output.h>
#include <processors/circular_buffer.h>
#include <processors/trasnformer.h>

#include <sensors/analog_sensor.h>
#include <sensors/digital_sensor.h>
#include <sensors/temperature/lm35.h>
#include <actuator/pump.h>
#include <actuator/led.h>

CircularBuffer<int> circular = CircularBuffer<int>(30);
AnalogSensor pot_sensor = AnalogSensor(0x7A, A3);
Pump pump = Pump(0xAB, 7);
Led led = Led(0xAC, 13);


void setup() {
  Serial.begin(9600);
  pinMode(CONFIG::SENSOR_INPUNT, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  pot_sensor.excecute();
  if(pot_sensor.hasChanged()){
    ValueABC<float> value = pot_sensor.getValue();

    valuePrinter(Serial, value.getValue(), "Lectura potenciometro");
    
    //float mean=pot_sensor.getValue();
    circular.append(value.getValue());
    int mean = circular.mean();

    valuePrinter(Serial, mean, "Mean Value");
     
    //valuePrinter(Serial, mean, "Mean Value");
   // valuePrinter(Serial, raw_read, "Proc Value");
   
    //float lectura=analogRead(3);
    //float trans=map(lectura,30,1000,0,100);
    
    // PID: Va aquí;

    //pump.setValue(value);
    led.setValue(value);
  }
  //pump.excecute();
  //led.excecute();
  //digitalWrite(13,HIGH);


}