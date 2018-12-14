#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h> //Librairie du bus OneWire
#include <DallasTemperature.h> //Librairie du capteur
#include <EEPROM.h>

class Ceinture{
  private:
  // heart rate sensor variables
  double heartRate=70;
  PulseOximeter pox;
  

  // temperature sensor variables
  double temperature=0;
  double lastTemp = 0;
  int tempTimeSample = 1000;
  int divider = 1;

  public:
  void begin();
  void update();
  double getTemperature();
  double getHeartRate();
  void display();
};

