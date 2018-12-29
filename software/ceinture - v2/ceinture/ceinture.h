#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h> //Librairie du bus OneWire
#include <DallasTemperature.h> //Librairie du capteur
#include <EEPROM.h>
#include <arduinoFFT.h>

#define SAMPLE_NUMBER 64
#define SAMPLE_FREQUENCY 5

#define PIN_RESPIRATORY_SENSOR A3
#define PIN_TEMPERATURE_SENSOR A2

class Ceinture{
  private:
  // heart rate sensor variables
  double heartRate=70;
  PulseOximeter pox;

  // respiratory rate sensor
  double vReal[SAMPLE_NUMBER];
  double vImag[SAMPLE_NUMBER];
  int i=0;
  unsigned long lastResp = 0;
  double respiratoryRate;
  arduinoFFT FFT = arduinoFFT();
  

  // temperature sensor variables
  double temperature=0;
  double lastTemp = 0;

  public:
  void begin();
  void update();
  double getTemperature();
  double getHeartRate();
  double getRespiratoryRate();
  void display();
};

