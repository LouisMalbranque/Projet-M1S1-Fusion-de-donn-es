#include "ceinture.h"
Ceinture ceinture;

#define SAMPLE_PERIOD_FREQUENCY 4000

unsigned long lastMs=0;
void setup() {
  // put your setup code here, to run once:
  ceinture.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  ceinture.update();
  
  if (millis() - lastMs > 13000){
    double temp = ceinture.getTemperature();
    double heartRate = ceinture.getHeartRate();
    ceinture.getRespiratoryRate();
    ceinture.display();
    lastMs = millis();
  }
  
}
