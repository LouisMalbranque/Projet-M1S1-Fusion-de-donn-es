#include "ceinture.h"
Ceinture ceinture;

const int L1 = 13;   //Warning Led
long last = 0;
//double data_Resp[15];
//double data_Hrt[15];
int i = 0;
double sum_R = 0;
double sum_H = 0;
double moy_R = 0;
double moy_H = 0;
const float FCM=208.754-0.734 * 21; //calcul FCm en fonction de l'age (ici 21)
double prediction_RR = 0;
double prediction_HR = 0;
double sens = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(L1,OUTPUT);
  digitalWrite(L1,HIGH);
  delay(1000);
  digitalWrite(L1,LOW);
  ceinture.begin();
  for (int j =0; j<240;j++){
    EEPROM[j]=0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  ceinture.update();
  if (millis()-last> 30000 && i < 240) {    //wait 30 sec
    last=millis();
    Serial.println("----------------------------");
    //Si le coureur n'a pas couru a cet instant t:
    if(EEPROM[i] == 0){
      Serial.println("First course");                
      double current_Resp = ceinture.getRespiratoryRate();
      double current_Hrt = ceinture.getHeartRate(); 
      Serial.print("Heart Rate");
      Serial.println(current_Hrt);
      Serial.print("Respirative Rate");
      Serial.println(current_Resp*60);
      if(current_Hrt<=FCM){   //Tout va bien pour le coureur
        Serial.println("Runner OK");
        EEPROM[i] = current_Hrt;  //récupération de la fréquence cardiaque
        EEPROM[i+1] = current_Resp;    // récupération de la fréquence respiratoire 
        digitalWrite(L1,LOW); //LED eteinte
      }
      else{
        Serial.println("Runner too fast");
        EEPROM[i] = FCM*0.8;
        EEPROM[i+1] = ceinture.getRespiratoryRate();
        digitalWrite(L1,HIGH); //allume LED
      }
    }
    //Si les datas precedente existent:
    else{
      Serial.println("New Course");
      double current_Tmp = ceinture.getTemperature(); //On recup temperature
      if(current_Tmp < 10 || current_Tmp >28){
        sens=0;
      }
      else{
        sens=15;
      }
      Serial.print("Temperature exterieur :");
      Serial.println(current_Tmp);
      double current_Resp = ceinture.getRespiratoryRate();   //datas sensor
      double current_Hrt = ceinture.getHeartRate();
      prediction_RR=EEPROM[i+1];                 //Check predictions
      prediction_HR=EEPROM[i];
      Serial.print("Prediction HeartRate :");
      Serial.println(prediction_HR+sens);
      Serial.print("Current Heart Rate");
      Serial.println(current_Hrt);
      Serial.print("Prediction RespirationRate :");
      Serial.println(prediction_HR+sens);
      Serial.print("Current Respirative Rate");
      Serial.println(current_Resp*60);
      
      if(current_Hrt>=prediction_HR+sens){    //Si le coureur dépasse trop ancienne freq+sensi
        if(current_Resp>=prediction_RR){
          //Danger, il faut s'arreter
          digitalWrite(L1,HIGH);
        }
        else{
          //Warning, HR un peu haut
          digitalWrite(L1,HIGH);
        }
      }
      else{
        //Tout va bien
        digitalWrite(L1,LOW);
      }
      sum_R = sum_R - EEPROM[i+1]; // soustraction des échantillons précédents
      sum_H = sum_H - EEPROM[i];
      EEPROM[i+1] = ceinture.getRespiratoryRate();
      EEPROM[i] = ceinture.getHeartRate();
      sum_R = sum_R + EEPROM[i+1]; // ajout des derniers échantillons
      sum_H = sum_H + EEPROM[i];
            // calcul des moyennes
      moy_R = sum_R / (i+1);
      moy_H = sum_H / i;
  
      // mettons à jour les tableaux
      EEPROM[i+1] = moy_R;
      EEPROM[i] = moy_H;
    }
    i=i+2; // incrémentation indice
  }
}

