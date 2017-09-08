// Mains frequency measurement (Germany 50 Hz)
// measurement of fluctuations in mains frequency
// interrupt handler: mains frequency

#include <LiquidCrystal_I2C.h>


volatile unsigned long pulseCounter = 0; 
volatile unsigned long currentMicros;
volatile unsigned long previousMicros = 0;
volatile unsigned long duration = 0;

unsigned long _duration;
unsigned long _pulseCounter;
 // determine the time of averaging length
unsigned long measuringTime =  1000; // ms
unsigned long currentRuntime = 0;
unsigned long previousRuntime = 0; 

int overflow_state = 0; 


float freq; 

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

Serial.begin(115200);
lcd.begin();
lcd.print("Mains Frequency: ");
lcd.setCursor(7, 1);
lcd.print("Hz");


attachInterrupt(0, mains_freq_handler, RISING); // Pin 2 

}

void loop() {

 // number of milliseconds since the 
 // Arduino board began running the current program
currentRuntime = millis();

if (currentRuntime - previousRuntime >= measuringTime) {


  previousRuntime = currentRuntime;
  _duration = duration;
  _pulseCounter = pulseCounter;
  duration = 0;
  pulseCounter = 0;

  if(!overflow_state) {
  freq = 1e6 * _pulseCounter / (float(_duration)); 
  Serial.println(freq, 3);

  lcd.setCursor(0, 1);
  lcd.print(freq, 3); }
}
  else {
    overflow_state = 0; }
  
}

void mains_freq_handler() {

  if (previousMicros > micros()) {
  overflow_state = 1;
 }

 
  currentMicros = micros();
  duration += currentMicros - previousMicros;
  previousMicros = currentMicros;
  pulseCounter++; 
 
  
}



