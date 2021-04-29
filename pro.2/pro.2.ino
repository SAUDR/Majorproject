#include <rgb_lcd.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 255;
const int colorB = 255;


#define PIR_MOTION_SENSOR 6//Use pin 2 to receive the signal from the motion sensor  
#define REDLED 7 //red  LED is connected to D7 of Arduino
#define GREENLED 8 //green LED is connected to D8 of Arduino
#define buz  5 //buzzer is connected to D5 of Arduino
#define touch 4 //touch sensor is connected to D2 of Arduino

//blynk app
#define BLYNK_PRINT Serial
#include <Bridge.h>
#include <BlynkSimpleYun.h>
char auth[] = "XIitLWbqB252bQXCvopKCDHBl6DAKvtz";

void setup()
{

   //method to insilaise the pinMode 
  pinsInit();

    Serial.begin(9600);

  Blynk.begin(auth);

}

void loop()
{
   Blynk.run();
  if (isPeopleDetected()){ //if it detects the moving people?
    turnOnLED();
    delay(1000);
  }
  else{
    turnOffLED();
  }
}



void pinsInit()
{
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  pinMode(PIR_MOTION_SENSOR, INPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(touch,INPUT);
}


void turnOnLED()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  
  lcd.print("Watch OUT!!");
  
  digitalWrite(buz, HIGH);
  
  digitalWrite(GREENLED, LOW);
  
  digitalWrite(REDLED, HIGH);
  
  delay(500);
  
  digitalWrite(REDLED, LOW);
  delay(500);

 


}



void turnOffLED()
{

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GOOD TO GO");
  digitalWrite(buz, LOW);
  digitalWrite(REDLED, LOW);
  digitalWrite(GREENLED, HIGH);
}




boolean isPeopleDetected()
{
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  int TouchValue = digitalRead(touch);

  
  if (sensorValue == HIGH && TouchValue == HIGH ) //if the sensor value is HIGH?
  {
    return true;//yes,return ture
  }
  else
  {
    return false;//no,return false
  }
}
