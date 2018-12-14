#include "ceinture.h"
Ceinture ceinture;

long last=0;

void setup() {
  // put your setup code here, to run once:
  ceinture.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  ceinture.update();
  if (millis() - last > 3000){
    ceinture.getTemperature();
    ceinture.getHeartRate();
    ceinture.display();
    last = millis();
  }
}
