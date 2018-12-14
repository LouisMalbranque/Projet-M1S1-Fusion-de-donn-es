#include "ceinture.h"

  OneWire oneWire(2); //Bus One Wire sur la pin 2 de l'arduino
  DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
  DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie 
  
void Ceinture::begin(){
  Serial.begin(115200);
  Serial.print("Initializing temperature sensor..");
  sensors.begin(); //Activation des capteurs
  sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
  sensors.setResolution(sensorDeviceAddress, 9); //Résolutions possibles: 9,10,11,12
  Serial.println("SUCCESS");

  
  Serial.println("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
      Serial.println("FAILED");
  }else{
      Serial.println("SUCCESS");
  }

  Serial.println("Initialisation successful");
}

void Ceinture::update(){
  pox.update();
  /*if (millis()-lastTemp > tempTimeSample){
    sensors.requestTemperatures(); //Demande la température aux capteurs
    temperature = (temperature*divider + sensors.getTempCByIndex(0))/(divider+1);
    divider++;
    lastTemp = millis(); 
  }*/
}

double Ceinture::getTemperature(){
  //divider = 1;
  sensors.requestTemperatures(); //Demande la température aux capteurs
  temperature = sensors.getTempCByIndex(0);
  return temperature;
}

double Ceinture::getHeartRate(){
  double newRate = pox.getHeartRate();
  if ((newRate>60 and abs(newRate - heartRate)<20) || heartRate == 0) heartRate = newRate;
  pox.begin();
  return heartRate;
}

void Ceinture::display(){
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print("\tHeart Rate : ");
  Serial.print(heartRate);
  Serial.println();
}










