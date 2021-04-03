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

CircularBuffer<int> circular = CircularBuffer<int>(30);
AnalogSensor pot_sensor = AnalogSensor(0x7A, A3);
//Motor motor = Motor(0xAB, 7);
//Led led = Led(0xAC, 13);

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11

void setup() {
  Serial.begin(9600);
  pinMode(CONFIG::SENSOR_INPUNT, INPUT);
  pinMode(3, INPUT);
  pinMode(13, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

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

void loop() {
  pot_sensor.excecute();
  if(pot_sensor.hasChanged()){
    ValueABC<float> value = pot_sensor.getValue();

    valuePrinter(Serial, value.getValue(), "Lectura potenciometro");
    
    //float mean=pot_sensor.getValue();
    circular.append(value.getValue());
    int mean = circular.mean();

    valuePrinter(Serial, mean, "Mean Value");

    int scaled_read = scaler<int>(value.getValue(), 2.0);
    int mapped_read = analog_map<int>(value.getValue(), 0,100);

    valuePrinter(Serial, scaled_read, "Lectura escalada");
    valuePrinter(Serial, mapped_read, "Lectura mapeada");
     
    bool bool_value  = (50 < mapped_read);
    digitalWrite(13,bool_value);

    for (int i = 0; i < 8; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(mapped_read);
    }
   

    //pump.setValue(value);
    //led.setValue(value);
  }
  //pump.excecute();
  //led.excecute();
  //digitalWrite(13,HIGH);


}