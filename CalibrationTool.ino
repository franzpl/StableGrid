// Calibration of Arduino quartz ( 16 MHz) with a reference of 1 Hz 

#include <eRCaGuy_Timer2_Counter.h>
#include <DS3232RTC.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

unsigned long currentMicros;
unsigned long previousMicros = 0;
volatile unsigned long duration;
float quartz_freq; 
unsigned long measuringTime =  1000; // ms
unsigned long currentRuntime = 0;
unsigned long previousRuntime = 0; 

LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup()
{
  Serial.begin(115200); 
  RTC.squareWave(SQWAVE_1_HZ);
  lcd.begin();
  lcd.clear();    
  lcd.print("Calibration Tool ");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
  delay(3000);
  lcd.clear();
  lcd.print("Turn the adjustable");
  lcd.setCursor(0, 1);
  lcd.print("capacitor until the ");
  lcd.setCursor(0,2);
  lcd.print("output shows");
  lcd.setCursor(0,3);
  lcd.print("16.000000 MHz");
  delay(6000);
  lcd.clear(); 
  lcd.print("Start calibration... ");
  lcd.setCursor(9, 2);
  lcd.print(" MHz");
  timer2.setup();
  attachInterrupt(1, myinthandler, RISING);
}

void loop()
{
  currentRuntime = millis();
  
  if (currentRuntime - previousRuntime >= measuringTime) {
    
  previousRuntime = currentRuntime;
  quartz_freq = (16.0 / 1000000.0) * duration;
  lcd.setCursor(0, 2);
  lcd.print(quartz_freq, 6);
  Serial.print(quartz_freq, 6);
  Serial.println(" MHz");
  
  }
}

void myinthandler() {

  //currentMicros = micros() ;
  currentMicros = timer2.get_count() / 2.0;
  duration = currentMicros - previousMicros;
  previousMicros = currentMicros; 

}


 

