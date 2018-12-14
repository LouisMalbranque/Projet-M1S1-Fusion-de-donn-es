#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <OneWire.h> //Librairie du bus OneWire
#include <DallasTemperature.h> //Librairie du capteur
#include <EEPROM.h>

#define REPORTING_PERIOD_MS     10000
 
// PulseOximeter is the higher level interface to the sensor
// it offers:
//  * beat detection reporting
//  * heart rate calculation
//  * SpO2 (oxidation level) calculation
PulseOximeter pox;
 
uint32_t tsLastReport = 0;
OneWire oneWire(2); //Bus One Wire sur la pin 2 de l'arduino
DallasTemperature sensors(&oneWire); //Utilistion du bus Onewire pour les capteurs
DeviceAddress sensorDeviceAddress; //Vérifie la compatibilité des capteurs avec la librairie 
// Callback (registered below) fired when a pulse is detected

void onBeatDetected()
{
    Serial.println("Beat!");
}
 
void setup()
{
    Serial.begin(115200);
    Serial.print("Initializing temperature sensor..");
    sensors.begin(); //Activation des capteurs
    sensors.getAddress(sensorDeviceAddress, 0); //Demande l'adresse du capteur à l'index 0 du bus
    sensors.setResolution(sensorDeviceAddress, 9); //Résolutions possibles: 9,10,11,12


    
    Serial.print("Initializing pulse oximeter..");
 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
 
    // The default current for the IR LED is 50mA and it could be changed
    //   by uncommenting the following line. Check MAX30100_Registers.h for all the
    //   available options.
    // pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
 
 
    // Asynchronously dump heart rate and oxidation levels to the serial
    // For both, a value of 0 means "invalid"
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        
        Serial.print("Heart rate: ");
        Serial.print(pox.getHeartRate());
        sensors.requestTemperatures(); //Demande la température aux capteurs
        Serial.print(" temperature: "); 
        Serial.println(sensors.getTempCByIndex(0));
        tsLastReport = millis();
        if (!pox.begin()) {
          Serial.println("FAILED");
              for(;;);
          } else {
              Serial.println("SUCCESS");
         }
    }
    
}
